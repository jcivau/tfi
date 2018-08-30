<!DOCTYPE html>
<html lang="es">  
   <head>    
      <title>TFI Julian Civau</title>    
      <meta charset="UTF-8">
      <meta name="title" content="Título de la WEB">
      <meta name="description" content="Descripción de la WEB">    
      <!--<link href="http://dominio.com/hoja-de-estilos.css" rel="stylesheet" type="text/css"/>-->
   </head> 

   <body>
   <h1>TFI Julian Civau</h1>
   <p>Lorem ipsum dolor sit amet, consectetur adipisicing elit. Ipsa sint nesciunt doloremque, ratione officia, voluptate placeat recusandae, totam libero explicabo magnam labore a delectus commodi dolor iusto quae! Totam, officiis.</p>

<?php
   include("connect.php");
      
   $con=Connection();

   /*$temp1=$_POST["temp1"];
   $hum1=$_POST["hum1"];*/

   $temp1="15";
   $hum1="15";

   $insertar = "INSERT INTO `tempLog` (`temperature`, `humidity`) VALUES ('".$temp1."','".$hum1."')";

   if ($con->query($insertar) === FALSE) {
            echo "Error: " . $insertar . "<br>" . $con->error;
         }
      
   //mysql_query($query,$link);
   //mysql_close($link);
   $con->close();

   //header("Location: index.php");
   printf("HOLA!")
?>
   <a href="index.php">VOLVER!</a>

   </body>

</html>