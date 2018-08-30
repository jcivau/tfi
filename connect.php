<?php

	function Connection(){
		$servername = "localhost";
		$username = "victorhu_tfi";
		$password = "uxkpqchvTR6^";
		$base = "victorhu_tfi";

		// Create connection
		$con = new mysqli($servername, $username, $password, $base);

		/* comprobar la conexión */
		if (mysqli_connect_errno()) {
		printf("Falló la conexión al Inicio: %s\n", mysqli_connect_error());
		exit();
		}

		return $con;
	}
?>
