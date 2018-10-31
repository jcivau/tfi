<?php
   include("connect.php");
      
   $con=Connection();

   /*$temp1=$_POST["temp1"];
   $hum1=$_POST["hum1"];*/


   $insertar = "INSERT INTO `tempLog` (`temperature`, `humidity`) VALUES ('".$_GET["temp1"]."', '".$_GET["hum1"]."')";

   if ($con->query($insertar) === FALSE) {
            echo "Error: " . $insertar . "<br>" . $con->error;
         }

   $con->close();

   header("Location: index.php");
?>