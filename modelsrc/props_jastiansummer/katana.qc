$staticprop
$modelname "props_jastiansummer/katana"
$scale "0.500000"
$body "Body" "katana_ref"
$cdmaterials "models/props_jastiansummer/katana"
$sequence idle "katana_ref"
$surfaceprop "no_decal"
$collisionmodel "katana_phys"  {
	$maxconvexpieces 5
	$automass
}
$keyvalues {
	"prop_data" {
		base		Item.Small
		health		0
		allowstatic	true
		breakable_model	MetalChunks
		breakable_count	5
		breakable_skin	0
	}
}
