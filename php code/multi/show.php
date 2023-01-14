<html>
    <head>
        <meta http-equiv="refresh" content="3">
    </head>
    <body>
        <?php
            $servername = "localhost"; //ชื่อ Server
            $username = "root"; //Username
            $password = ""; //Password
            $dbname = "multi_arduino_data"; //ชื่อฐานขอมูล
            // Create connection
            $conn = new mysqli($servername, $username, $password, $dbname);
            // Check connection
            if ($conn->connect_error) 
            {
                die("Connection failed: " . $conn->connect_error);
            }
            //คําสั่ง sql สําหรับเรียกดูขอมูลจากฐานขอมูล
            $sql = "SELECT * FROM device_data ORDER by id_data DESC LIMIT 100";
            $result = $conn->query($sql);

            if ($result->num_rows > 0) 
            {
            // output data of each row
            echo "<table border='1'><th>No.</th><th>TEMP</th><th>HUMID</th><th>DATETIME</th><th>Device_ID</th>";
            while($row = $result->fetch_assoc()) 
            {
                echo "<tr>";
                echo "<td>".$row['id_data']."</td>";
                echo "<td>".$row['temp']."</td>";
                echo "<td>".$row['humidity']."</tad>";
                echo "<td>".$row['day']."</td>";
                echo "<td>".$row['id_device']."</td>";
                echo "</tr>";
            }

            echo "</table>";
            } else 
            {
                echo "0 results";
            }
            $conn->close();
        ?>
    </body>
</html>