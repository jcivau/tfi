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
		<link rel="stylesheet" href="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/css/bootstrap.min.css" integrity="sha384-MCw98/SFnGE8fJT3GXwEOngsV7Zt27NXFoaoApmYm81iuXoPkFOJwJ8ERdknLPMO" crossorigin="anonymous">
		<!--<con href="http://dominio.com/hoja-de-estilos.css" rel="stylesheet" type="text/css"/>-->
	</head> 
<body>

	<div class="container-fluid">
  		<div class="row">
    		<div class="col">
      			<h1>TFI Julian Civau</h1>
    		</div>
    		<div class="col">
      			<p>
   					<a href="https://tfi.plazacontenidos.com/add.php" target="_blank">Agregar dato</a>
   				</p>
    		</div>
  		</div>
	</div>

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

<script src="https://code.jquery.com/jquery-3.3.1.slim.min.js" integrity="sha384-q8i/X+965DzO0rT7abK41JStQIAqVgRVzpbzo5smXKp4YfRvH+8abtTE1Pi6jizo" crossorigin="anonymous"></script>
<script src="https://cdnjs.cloudflare.com/ajax/libs/popper.js/1.14.3/umd/popper.min.js" integrity="sha384-ZMP7rVo3mIykV+2+9J3UJ46jBk0WLaUAdn689aCwoqbBJiSnjAK/l8WvCWPIPm49" crossorigin="anonymous"></script>
<script src="https://stackpath.bootstrapcdn.com/bootstrap/4.1.3/js/bootstrap.min.js" integrity="sha384-ChfqqxuZUCnJSK3+MXmPNIyE6ZbWh2IMqE241rYiqJxyMiZ6OW/JmZQ5stwEULTy" crossorigin="anonymous"></script>
</body>
</html>
