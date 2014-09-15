<?php

$file = fopen("co.txt", "r") or die("Unable to open file");
while(!feof($file)) {
  echo fgets($file);
}
fclose($tempf);

?>


