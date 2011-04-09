$staticprop
$modelname "props_jastiansummer/railings/corner_in"
$body "Body" "corner_in_ref"
$cdmaterials "models/props_jastiansummer/railings"
$sequence idle "corner_in_ref"
$surfaceprop "metal"
$collisionmodel "corner_in_phys"  {
	$concave
	$maxconvexpieces 4
	$automass
}
$lod 40
{
	replacemodel "corner_in_ref" "corner_in_lod"
}