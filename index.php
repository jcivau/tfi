<?php

	include("connect.php"); 	
	
	$con=Connection();

	//$result=mysqli_query("SELECT * FROM `tempLog` ORDER BY `timeStamp` DESC",$con);

	//CONSULTAS SOBRE MENUES VEGETARIANOS
	//$consulta = "SELECT * FROM menues_casino where fecha = '$fecha'";
	$consulta = "SELECT * FROM `tempLog` ORDER BY `timeStamp` DESC";
?>

<!DOCTYPE html>
<html lang="es">  
	<head>    
		<title>TFI Julian Civau</title>    
		<meta charset="UTF-8">
		<meta name="title" content="Título de la WEB">
		<meta name="description" content="Descripción de la WEB">    
		<!--<con href="http://dominio.com/hoja-de-estilos.css" rel="stylesheet" type="text/css"/>-->
	</head> 
<body>
   <h1>Medidor de Humedad y Temperatura</h1>

   <p>
   		<a href="https://tfi.plazacontenidos.com/add.php" target="_blank">Agregar dato</a>
   	</p>

   <table border="1" cellspacing="1" cellpadding="1">
		<tr>
			<td>&nbsp;Fecha y Hora&nbsp;</td>
			<td>&nbsp;Temperatura&nbsp;</td>
			<td>&nbsp;Humedad&nbsp;</td>
		</tr>

    <?php

		// Ejecuto la consulta
		if ($resultado = $con->query($consulta)) {

			while ($row = $resultado->fetch_assoc()) {
		        		printf("<tr><td> &nbsp;%s </td><td> &nbsp;%s&nbsp; </td><td> &nbsp;%s&nbsp; </td></tr>", 
		           		$row["timeStamp"], $row["temperature"], $row["humidity"]);
		  	}

		}else echo "Fallo la Consulta";

	$con->close();
	//db_close($con);
	?>

   </table>
</body>
</html>
