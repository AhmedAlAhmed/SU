<?php

        require_once  'dbconfig.php';
        $charset = "abcdefghijklm";
        $charset .= strtoupper($charset) . 'nopqrst56789uvwxuz01234';
        $charset .= strtoupper('nopqrst56789uvwxuz01234');




        function rep($str){
            global $charset;

            for($i = 0; $i< strlen($charset); $i++){
                $charset = str_shuffle($charset);
                $str .= $charset[ $i ];

                if(strlen($str) > 10) return $str;
                else rep($str);

            }
        }


        function generate_code(){
            return rep("");
        }


        function is_url_found($url){
            $url = trim(($url));
            global $conn;
            $stmt = $conn->prepare("SELECT * FROM URLs WHERE IP LIKE :u");
            $stmt->bindValue(':u', $url);
            $stmt->execute();
            $res = $stmt->fetchAll(PDO::FETCH_ASSOC);
            if(count($res) > 0){
                # found
                return $res[0]['URL'];
            }else{
                return FALSE;
            }
        }

        function is_code_found($code){
            $code = trim(($code));
            global $conn;
            $stmt = $conn->prepare("SELECT * FROM URLs WHERE URL LIKE :u");
            $stmt->bindValue(':u', $code);
            $stmt->execute();
            $res = $stmt->fetchAll(PDO::FETCH_ASSOC);
            if(count($res) > 0){
                # found
                return $res[0]['IP'];
            }else{
                return FALSE;
            }
        }

        function insert_url_code_pair($url, $code){
            $code = trim(($code));
            $url = trim(($url));
            if(filter_var($url, FILTER_VALIDATE_URL) === FALSE){
                return FALSE;
            }
            global $conn;
            $stmt = $conn->prepare("INSERT INTO URLs(IP, URL) VALUES(:IP, :URL)");

            $stmt->bindValue(':IP', $url);
            $stmt->bindValue(':URL', $code);
            $stmt->execute();

        }


        function get_short_url($url){
            if(filter_var($url, FILTER_VALIDATE_URL) === FALSE){
                return FALSE;
            }
            $check_url = is_url_found($url);
            if($check_url !== FALSE){
                # Found
                return $check_url;
            }else{
                $code = generate_code();
                while(is_code_found($code)){
                    $code = generate_code();
                }

                insert_url_code_pair($url, $code);
                return $code;
            }
        }

?>

