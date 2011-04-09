$staticprop
$modelname "props_jastiansummer/railings/straight_64"
$body "Body" "straight_64_ref"
$cdmaterials "models/props_jastiansummer/railings"
$sequence idle "straight_64_ref"
$surfaceprop "metal"
$collisionmodel "straight_64_phys"
{
	$concave
	$maxconvexpieces 5
	$automass
}
$lod 40
{
	replacemodel "straight_64_ref" "straight_64_lod"
}