<?php
$co = $_GET['co'];
echo (string)$co;
$file = fopen("co.txt", "w") or die("Unable to open file");
fwrite($file, (string)$co);
fclose($file);
?>