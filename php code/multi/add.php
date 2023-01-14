<?php
    $t1 = $_POST['t1']; //คาที่ Get จาก Arduino
    $h1 = $_POST['h1'];
    $t2 = $_POST['t2']; //คาที่ Get จาก Arduino
    $h2 = $_POST['h2'];
    $t3 = $_POST['t3']; //คาที่ Get จาก Arduino
    $h3 = $_POST['h3'];

    $servername = "localhost"; //ชื่อ Server
    $username = "root"; //Username
    $password = ""; //Password
    $dbname = "multi_arduino_data"; //ชื่อฐานขอมูล
    // Create connection
    $conn = new mysqli($servername, $username,$password, $dbname);
    // Check connection
    if ($conn->connect_error) 
    {
        die("Connection failed: " . $conn->connect_error);
    }
    //$val = $_GET['temp']; คําสั่ง sql สําหรับเพิ่มขอมูลลงฐานขอมูล
    $sql = "INSERT INTO device_data(id_data,temp,humidity,day,id_device) VALUES (null,$t1,$h1,null,1);";
    $conn->query($sql);
    $sql = "INSERT INTO device_data(id_data,temp,humidity,day,id_device) VALUES (null,$t2,$h2,null,2);";
    $conn->query($sql);
    $sql = "INSERT INTO device_data(id_data,temp,humidity,day,id_device) VALUES (null,$t3,$h3,null,3);";
    $conn->query($sql);

    $conn->close();
?>