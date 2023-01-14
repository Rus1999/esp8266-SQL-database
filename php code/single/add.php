<?php
    $temp = $_GET['temp']; //คาที่ Get จาก Arduino
    $humid = $_GET['humid'];
    $servername = "localhost"; //ชื่อ Server
    $username = "root"; //Username
    $password = ""; //Password
    $dbname = "arduino_data"; //ชื่อฐานขอมูล
    // Create connection
    $conn = new mysqli($servername, $username,$password, $dbname);
    // Check connection
    if ($conn->connect_error) 
    {
        die("Connection failed: " . $conn->connect_error);
    }
    //$val = $_GET['temp']; คําสั่ง sql สําหรับเพิ่มขอมูลลงฐานขอมูล
    $sql = "INSERT INTO dhtdata(id,temp,humid,day) VALUES (null,$temp,$humid,null);";

    if ($conn->query($sql) === TRUE) 
    {
        echo "save OK";
    } else 
    {
        echo "Error:" . $sql . "<br>" . $conn->error;
    }

    $conn->close();
?>