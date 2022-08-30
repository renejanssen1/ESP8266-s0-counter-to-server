<?php
	$count = $_GET["int"];
	$pulsetime = $_GET["puls"];

	$date = date('Y-m-d');
	$output = "";
	$myFile = "test.log";
	if (!file_exists($myFile)) {
		echo 'File not found';
	}
	$fh = fopen($myFile, 'a') or die("couldn't open");
	$output .= date('H:i:s');
	$output .= " - ";
	$output .= "Aantal pulsjes: ";
	$output .= $count;
	$output .= " - ";
	$output .= "Pulsetijd: ";
	$output .= $pulsetime;	
	$output .= "\n";
	fwrite($fh, $output );
	fclose($fh);
?>