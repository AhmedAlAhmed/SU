<?php
/**
 * Created by PhpStorm.
 * User: root
 * Date: 25/09/16
 * Time: 04:32 م
 */

$server_name = '127.0.0.1';
$username = 'root';
$pass = 'root';

try{

    $conn = new PDO("mysql:host=$server_name;dbname=shorturlDB", $username, $pass);
    $conn->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);


}catch(PDOException $e){
    print 'PDOException : ' . $e->getMessage();
}













?>
