<html>
    <head>
        <meta http-equiv="refresh" content="3">
    </head>
    <body>
        <?php
            $servername = "localhost"; //ชื่อ Server
            $username = "root"; //Username
            $password = ""; //Password
            $dbname = "arduino_data"; //ชื่อฐานขอมูล
            // Create connection
            $conn = new mysqli($servername, $username, $password, $dbname);
            // Check connection
            if ($conn->connect_error) 
            {
                die("Connection failed: " . $conn->connect_error);
            }
            //คําสั่ง sql สําหรับเรียกดูขอมูลจากฐานขอมูล
            $sql = "SELECT * FROM dhtdata ORDER by id DESC LIMIT 100";
            $result = $conn->query($sql);

            if ($result->num_rows > 0) 
            {
            // output data of each row
            echo "<table border='1'><th>ID</th><th>TEMP</th><th>HUMID</th><th>DATETIME</th>";
            while($row = $result->fetch_assoc()) 
            {
                echo "<tr>";
                echo "<td>".$row['id']."</td>";
                echo "<td>".$row['temp']."</td>";
                echo "<td>".$row['humid']."</tad>";
                echo "<td>".$row['day']."</td>";
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