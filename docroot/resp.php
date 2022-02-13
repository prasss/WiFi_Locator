<?php
$q = $_REQUEST["q"];

$hint = "Response";

// lookup all hints from array if $q is different from ""
if ($q !== "") {
  echo $hint . $q;
}
  ?>
