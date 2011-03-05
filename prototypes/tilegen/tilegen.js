var canvas = document.getElementById( 'c' ),
	ctx = canvas.getContext( '2d' );

var DOOR_CAVE = 0, DOOR_WEB = 1, DOOR_HIVE = 2,
	doorColors = ['#333', '#eee', '#fe6'],
	ORIENTATION_0 = 0, ORIENTATION_90 = Math.PI / 2, ORIENTATION_180 = Math.PI, ORIENTATION_270 = 3 * Math.PI / 2,
	TILE_UNIT = 32, tileTypes = [], tiles = [];

function redrawAll(highQuality) {
	ctx.clearRect( -1, -1, canvas.width + 2, canvas.height + 2 );
	ctx.beginPath();
	for ( var i = TILE_UNIT; i < canvas.width; i += TILE_UNIT ) {
		ctx.moveTo( i, 0 );
		ctx.lineTo( i, canvas.height );
	}
	for ( var i = TILE_UNIT; i < canvas.width; i += TILE_UNIT ) {
		ctx.moveTo( 0, i );
		ctx.lineTo( canvas.width, i );
	}
	ctx.stroke();

	if ( !highQuality ) {
		for ( var x = 0; x < canvas.width / TILE_UNIT; x++ ) {
			for ( var y = 0; y < canvas.height / TILE_UNIT; y++ ) {
				if ( SpaceTaken( x, y ) )
					ctx.fillRect( x * TILE_UNIT, y * TILE_UNIT, TILE_UNIT, TILE_UNIT );
			}
		}
	}

	if ( highQuality ) {
		for ( var i = 0; i < tiles.length; i++ ) {
			tiles[i].draw();
		}
	} else {
		for ( var i = 0; i < tiles.length; i++ ) {
			tiles[i].drawBlock();
		}
	}
}
redrawAll();

function DoorCount( x, y, door ) {
	var count = 0;
	for ( var i = 0; i < tiles.length; i++ ) {
		var t = tiles[i];
		if ( t._x > x + 1 || t._y > y + 1 )
			continue;
		if ( t._x + t.sizeX < x || t._y + t.sizeY < y )
			continue;
		var _x = x - t._x, _y = y - t._y;
		if ( _y == t.sizeY && _x == t.sizeX )
			continue;
		if ( door == 2 && _y == -1 ) {
			if ( t.doors[_x] && t.doors[_x].indexOf( 0 ) > -1 )
				count++;
			continue;
		}
		if ( door == 1 && _x == -1 ) {
			if ( t.doors[_y * t.sizeX] && t.doors[_y * t.sizeX].indexOf( 3 ) > -1 )
				count++;
			continue;
		}
		if ( t._x > x || t._y > y )
			continue;
		if ( door == 0 && _y == t.sizeY ) {
			if ( t.doors[_x + (_y - 1) * t.sizeX] && t.doors[_x + (_y - 1) * t.sizeX].indexOf( 2 ) > -1 )
				count++;
			continue;
		}
		if ( door == 3 && _x == t.sizeX ) {
			if ( t.doors[_x - 1 + _y * t.sizeX] && t.doors[_x - 1 + _y * t.sizeX].indexOf( 1 ) > -1 )
				count++;
			continue;
		}
		if ( _y == t.sizeY || _x == t.sizeX )
			continue;
		if ( t.doors[_x + _y * t.sizeX] && t.doors[_x + _y * t.sizeX].indexOf( door ) > -1 )
			count++;
	}
	return count;
}
function getEnclosedSpaces( tile ) {
	if ( !tile )
		tile = this;

	var s = tile.sizeX;

	var enclosed = new Array( s * tile.sizeY );

	var e = false;
	for ( var y = 0; y < tile.sizeY; y++ ) {
		for ( var x = 0; x < s; x++ ) {
			for ( var i = 0; i < tile.doors[y * s + x].length; i++ ) {
				if ( tile.doors[y * s + x][i] == 3 )
					e = true;
			}
			for ( var i = 0; i < tile.walls[y * s + x].length; i++ ) {
				if ( tile.walls[y * s + x][i] == 3 )
					e = true;
			}
			enclosed[y * s + x] = e;
			for ( var i = 0; i < tile.doors[y * s + x].length; i++ ) {
				if ( tile.doors[y * s + x][i] == 1 )
					e = false;
			}
			for ( var i = 0; i < tile.walls[y * s + x].length; i++ ) {
				if ( tile.walls[y * s + x][i] == 1 )
					e = false;
			}
		}
		e = false;
	}
	for ( var x = 0; x < s; x++ ) {
		for ( var y = 0; y < tile.sizeY; y++ ) {
			for ( var i = 0; i < tile.doors[y * s + x].length; i++ ) {
				if ( tile.doors[y * s + x][i] == 0 )
					e = true;
			}
			for ( var i = 0; i < tile.walls[y * s + x].length; i++ ) {
				if ( tile.walls[y * s + x][i] == 0 )
					e = true;
			}
			enclosed[y * s + x] |= e;
			for ( var i = 0; i < tile.doors[y * s + x].length; i++ ) {
				if ( tile.doors[y * s + x][i] == 2 )
					e = false;
			}
			for ( var i = 0; i < tile.walls[y * s + x].length; i++ ) {
				if ( tile.walls[y * s + x][i] == 2 )
					e = false;
			}
		}
		e = false;
	}

	return enclosed;
}
function SpaceTaken( x, y ) {
	for ( var i = 0; i < tiles.length; i++ ) {
		if ( tiles[i]._x > x || tiles[i]._y > y )
			continue;
		if ( tiles[i]._x + tiles[i].sizeX <= x || tiles[i]._y + tiles[i].sizeY <= y )
			continue;

		/*var enclosed = false;
		// For a space to be taken, it must be enclosed on at least one side by a wall that is not matched before the space.
		// Left
		for ( var j = 0, row = ( y - tiles[i]._y ) * tiles[i].sizeX; j < x - tiles[i]._x; j++ ) {
			if ( tiles[i].walls[row + j].indexOf( 3 ) > -1 )
				enclosed = true;
			if ( tiles[i].walls[row + j].indexOf( 1 ) > -1 )
				enclosed = false;
		}
		if ( enclosed )
			return true;
		// Right
		for ( var j = tiles[i].sizeX - 1, row = ( y - tiles[i]._y ) * tiles[i].sizeX; j > x - tiles[i]._x; j-- ) {
			if ( tiles[i].walls[row + j].indexOf( 1 ) > -1 )
				enclosed = true;
			if ( tiles[i].walls[row + j].indexOf( 3 ) > -1 )
				enclosed = false;
		}
		if ( enclosed )
			return true;
		// Top
		for ( var j = 0, col = x - tiles[i]._x; j < y - tiles[i]._y; j++ ) {
			if ( tiles[i].walls[col + j * tiles[i].sizeX].indexOf( 0 ) > -1 )
				enclosed = true;
			if ( tiles[i].walls[col + j * tiles[i].sizeX].indexOf( 2 ) > -1 )
				enclosed = false;
		}
		if ( enclosed )
			return true;
		// Bottom
		for ( var j = tiles[i].sizeY - 1, col = x - tiles[i]._x; j > y - tiles[i]._y; j-- ) {
			if ( tiles[i].walls[col + j * tiles[i].sizeX].indexOf( 2 ) > -1 )
				enclosed = true;
			if ( tiles[i].walls[col + j * tiles[i].sizeX].indexOf( 0 ) > -1 )
				enclosed = false;
		}
		if ( enclosed )
			return true;*/

		if ( tiles[i].getEnclosedSpaces()[x - tiles[i]._x + tiles[i].sizeX * (y - tiles[i]._y)] ) {
			return true;
		}
	}
	return false;
}
function TileAllowed( tile ) {
	if ( tile._x < 0 || tile._y < 0 || tile._x + tile.sizeX > canvas.width / TILE_UNIT || tile._y + tile.sizeY > canvas.width / TILE_UNIT )
		return false;

	//for ( var i = 0; i < tiles.length; i++ ) {
	//	if ( tiles[i]._x == tile._x && tiles[i]._y == tile._y )
	//		return false; // Same origin
	//	if ( tiles[i]._x < tile._x + tile.sizeX && tiles[i]._x + tiles[i].sizeX > tile._x &&
	//		tiles[i]._y < tile._y + tile.sizeY && tiles[i]._y + tiles[i].sizeY > tile._y )
	//		return false; // Overlapping
	//}

	var enclosed = tile.getEnclosedSpaces();
	for ( var i = 0; i < enclosed.length; i++ ) {
		if ( enclosed[i] && SpaceTaken( i % tile.sizeX + tile._x, ~~( i / tile.sizeX ) + tile._y ) )
			return false;
	}

	var doors = tile.getDoors();
	for ( var i = 0; i < doors.length; i++ ) {
		if ( DoorCount( doors[i][0], doors[i][1], doors[i][2] ) == 0 )
			continue;
		if ( DoorCount( doors[i][0], doors[i][1], doors[i][2] ) > 1 )
			return false;
		for ( var j = 0; j < tiles.length; j++ ) {
			var _doors = tiles[j].getDoors(), returnFalseIfNotFound = false, foundDoor = false;
			for ( var k = 0; k < _doors.length; k++ ) {
				switch ( doors[i][2] ) {
					case 0:
						if ( _doors[k][0] == doors[i][0] && _doors[k][1] == doors[i][1] - 1 ) {
							if ( _doors[k][2] == 2 ) {
								if ( _doors[k][3] != doors[i][3] )
									return false;
								foundDoor = true;
							} else
								returnFalseIfNotFound = true;
						}
						break;
					case 1:
						if ( _doors[k][0] == doors[i][0] + 1 && _doors[k][1] == doors[i][1] ) {
							if ( _doors[k][2] == 3 ) {
								if ( _doors[k][3] != doors[i][3] )
									return false;
								foundDoor = true;
							} else
								returnFalseIfNotFound = true;
						}
						break;
					case 2:
						if ( _doors[k][0] == doors[i][0] && _doors[k][1] == doors[i][1] + 1 ) {
							if ( _doors[k][2] == 0 ) {
								if ( _doors[k][3] != doors[i][3] )
									return false;
								foundDoor = true;
							} else
								returnFalseIfNotFound = true;
						}
						break;
					case 3:
						if ( _doors[k][0] == doors[i][0] - 1 && _doors[k][1] == doors[i][1] ) {
							if ( _doors[k][2] == 1 ) {
								if ( _doors[k][3] != doors[i][3] )
									return false;
								foundDoor = true;
							} else
								returnFalseIfNotFound = true;
						}
						break;
				}
				if ( foundDoor )
					break;
			}
			if ( returnFalseIfNotFound && !foundDoor )
				return false;
		}
		switch ( doors[i][2] ) {
			case 0:
				if ( SpaceTaken( doors[i][0], doors[i][1] - 1 ) && !DoorCount( doors[i][0], doors[i][1], 0 ) )
					return false;
				break;
			case 1:
				if ( SpaceTaken( doors[i][0] + 1, doors[i][1] ) && !DoorCount( doors[i][0], doors[i][1], 1 ) )
					return false;
				break;
			case 2:
				if ( SpaceTaken( doors[i][0], doors[i][1] + 1 ) && !DoorCount( doors[i][0], doors[i][1], 2 ) )
					return false;
				break;
			case 3:
				if ( SpaceTaken( doors[i][0] - 1, doors[i][1] ) && !DoorCount( doors[i][0], doors[i][1], 3 ) )
					return false;
				break;
		}
	}
	return true;
}
function build() {
	if (this == (function(){return this})())
		return;
	if ( tiles.indexOf( this ) == -1 )
		return;

	var candidates = [], doors = this.getDoors();
	for ( var i = 0; i < doors.length; i++ ){
		if ( DoorCount( doors[i][0], doors[i][1], doors[i][2] ) == 1 ) {
			for ( var k = 0; k < 30; k++ ) {
				var candidate = new Straight( [doors[i][3], ~~( Math.random() * 3 )], ( ( -doors[i][2] + 5 ) % 4 ) * Math.PI / 2, doors[i][0] + Straight.doorOffsetDir[doors[i][2]][0], doors[i][1] + Straight.doorOffsetDir[doors[i][2]][1] );
				if ( TileAllowed( candidate ) )
					candidates.push(candidate);
			}
			for ( var k = 0; k < 10; k++ ) {
				var candidate = new Turn( [doors[i][3], ~~( Math.random() * 3 )], (function(d){switch(d){case 0:return 3;case 1:return 0;case 2:return 1;case 3:return 2;}})(doors[i][2]) * Math.PI / 2, doors[i][0] + Turn.doorOffsetDir[doors[i][2]][0], doors[i][1] + Turn.doorOffsetDir[doors[i][2]][1] );
				if ( TileAllowed( candidate ) )
					candidates.push(candidate);
			}
			for ( var k = 0; k < 10; k++ ) {
				var candidate = new Turn( [doors[i][3], ~~( Math.random() * 3 )], (function(d){switch(d){case 0:return 0;case 1:return 1;case 2:return 2;case 3:return 3;}})(doors[i][2]) * Math.PI / 2, doors[i][0] + Turn.doorOffsetDir[doors[i][2] + 4][0], doors[i][1] + Turn.doorOffsetDir[doors[i][2] + 4][1] );
				if ( TileAllowed( candidate ) )
					candidates.push(candidate);
			}
		}
	}

	return candidates[~~( Math.random() * candidates.length )];
}
function getDoors( tile ) {
	if ( !tile )
		tile = this;
	if ( !tile.doors )
		return [];

	var doors = [];
	for ( var i = 0; i < tile.doors.length; i++ ) {
		for ( var j = 0; j < tile.doors[i].length; j++ ) {
			doors.push( [tile._x + i % tile.sizeX, tile._y + ~~(i / tile.sizeX), tile.doors[i][j], tile.doorTypes[i][j]] );
		}
	}
	return doors;
}
function draw() {
	var _segments = [];
	for ( var x = 0; x < this.sizeX; x++ ) {
		for ( var y = 0; y < this.sizeY; y++ ) {
			var walls = this.walls[x + y * this.sizeX];
			for ( var i = 0; i < walls.length; i++ ) {
				switch ( walls[i] ) {
					case 0:
						_segments.push( [x * TILE_UNIT + ( walls.indexOf( 3 ) > -1 ? TILE_UNIT / 8 : ( ( x > 0 && y > 0 && this.walls[x - 1 + y * this.sizeX - this.sizeX].indexOf( 1 ) > -1 ) ? -TILE_UNIT / 8 : 0 ) ), y * TILE_UNIT + TILE_UNIT / 8, x * TILE_UNIT + TILE_UNIT - ( walls.indexOf( 1 ) > -1 ? TILE_UNIT / 8 : ( ( x < this.sizeX - 1 && y > 0 && this.walls[x + 1 + y * this.sizeX - this.sizeX].indexOf( 3 ) > -1 ) ? -TILE_UNIT / 8 : 0 ) ), y * TILE_UNIT + TILE_UNIT / 8] );
						break;
					case 1:
						_segments.push( [x * TILE_UNIT + TILE_UNIT - TILE_UNIT / 8, y * TILE_UNIT + ( walls.indexOf( 0 ) > -1 ? TILE_UNIT / 8 : ( ( x < this.sizeX - 1 && y > 0 && this.walls[x + 1 + y * this.sizeX - this.sizeX].indexOf( 2 ) > -1 ) ? -TILE_UNIT / 8 : 0 ) ), x * TILE_UNIT + TILE_UNIT - TILE_UNIT / 8, y * TILE_UNIT + TILE_UNIT - ( walls.indexOf( 2 ) > -1 ? TILE_UNIT / 8 : ( ( x < this.sizeX - 1 && y < this.sizeY - 1 && this.walls[x + 1 + y * this.sizeX + this.sizeX].indexOf( 0 ) > -1 ) ? -TILE_UNIT / 8 : 0 ) ) ] );
						break;
					case 2:
						_segments.push( [x * TILE_UNIT + ( walls.indexOf( 3 ) > -1 ? TILE_UNIT / 8 : ( ( x > 0 && y < this.sizeY - 1 && this.walls[x - 1 + y * this.sizeX + this.sizeX].indexOf( 3 ) > -1 ) ? -TILE_UNIT / 8 : 0 ) ), y * TILE_UNIT + TILE_UNIT - TILE_UNIT / 8, x * TILE_UNIT + TILE_UNIT - ( walls.indexOf( 1 ) > -1 ? TILE_UNIT / 8 : ( ( x < this.sizeX - 1 && y < this.sizeY - 1 && this.walls[x + 1 + y * this.sizeX + this.sizeX].indexOf( 3 ) > -1 ) ? -TILE_UNIT / 8 : 0 ) ), y * TILE_UNIT + TILE_UNIT - TILE_UNIT / 8 ] );
						break;
					case 3:
						_segments.push( [x * TILE_UNIT + TILE_UNIT / 8, y * TILE_UNIT + ( walls.indexOf( 0 ) > -1 ? TILE_UNIT / 8 : ( ( x > 0 && y > 0 && this.walls[x - 1 + y * this.sizeX - this.sizeX].indexOf( 2 ) > -1 ) ? -TILE_UNIT / 8 : 0 ) ), x * TILE_UNIT + TILE_UNIT / 8, y * TILE_UNIT + ( TILE_UNIT - ( walls.indexOf( 2 ) > -1 ? TILE_UNIT / 8 : ( ( x > 0 && y < this.sizeY - 1 && this.walls[x - 1 + y * this.sizeX + this.sizeX].indexOf( 0 ) > -1 ) ? -TILE_UNIT / 8 : 0 ) ) )] );
						break;
				}
			}
		}
	}

	var allSegments = [], segments = [[_segments[0][0], _segments[0][1]], [_segments[0][2], _segments[0][3]]];
	_segments.shift();
	while ( _segments.length ) {
		var found = false;
		for ( var i = 0; i < _segments.length; i++ ) {
			if ( _segments[i][0] == segments[0][0] && _segments[i][1] == segments[0][1] ) {
				segments.unshift( [_segments[i][2], _segments[i][3]] );
				_segments.splice( i, 1 );
				found = true;
				break;
			} else if ( _segments[i][2] == segments[0][0] && _segments[i][3] == segments[0][1] ) {
				segments.unshift( [_segments[i][0], _segments[i][1]] );
				_segments.splice( i, 1 );
				found = true;
				break;
			} else if ( _segments[i][0] == segments[segments.length - 1][0] && _segments[i][1] == segments[segments.length - 1][1] ) {
				segments.push( [_segments[i][2], _segments[i][3]] );
				_segments.splice( i, 1 );
				found = true;
				break;
			} else if ( _segments[i][2] == segments[segments.length - 1][0] && _segments[i][3] == segments[segments.length - 1][1] ) {
				segments.push( [_segments[i][0], _segments[i][1]] );
				_segments.splice( i, 1 );
				found = true;
				break;
			}
		}
		if ( !found ) {
			allSegments.push( segments );
			segments = [[_segments[0][0], _segments[0][1]], [_segments[0][2], _segments[0][3]]];
			_segments.shift();
		}
	}

	function subdivide( points, iterations ) {
		var _points = [];

		_points.push( points[0] );
		for ( var i = 1; i < points.length; i++ ) {
			_points.push( [( points[i][0] + points[i - 1][0] ) / 2, ( points[i][1] + points[i - 1][1] ) / 2] );
			if ( iterations > 1 )
				_points.push( points[i] );
		}
		if ( iterations == 1 )
			_points.push( points[points.length - 1] );

		if ( --iterations > 0 )
			return subdivide( _points, iterations );
		return _points;
	}

	ctx.save();
	ctx.translate( this._x * TILE_UNIT + this.sizeX * TILE_UNIT / 2, this._y * TILE_UNIT + this.sizeY * TILE_UNIT / 2 );
	ctx.rotate( this._turn );
	ctx.translate( -this.sizeX * TILE_UNIT / 2, -this.sizeY * TILE_UNIT / 2 );
	ctx.beginPath();
	for ( var i = 0; i < allSegments.length; i++ ) {
		var sub = subdivide( allSegments[i], 2 );
		ctx.moveTo( sub[0][0], sub[0][1] );
		for ( var j = 1; j < sub.length; j++ ) {
			ctx.lineTo( sub[j][0], sub[j][1] );
		}
	}
	ctx.stroke();
	ctx.restore();
}
function drawBlock() {
	ctx.save();
	ctx.translate( this._x * TILE_UNIT + this.sizeX * TILE_UNIT / 2, this._y * TILE_UNIT + this.sizeY * TILE_UNIT / 2 );
	ctx.rotate( this._turn );
	ctx.translate( -this.sizeX * TILE_UNIT / 2, -this.sizeY * TILE_UNIT / 2 );
	for ( var x = 0; x < this.sizeX; x++ ) {
		for ( var y = 0; y < this.sizeY; y++ ) {
			ctx.save();
			ctx.translate( x * TILE_UNIT, y * TILE_UNIT );
			ctx.beginPath();
			var walls = this.walls[x + y * this.sizeX];
			for ( var i = 0; i < walls.length; i++ ) {
				switch ( walls[i] ) {
					case 0:
						ctx.moveTo( walls.indexOf( 3 ) > -1 ? TILE_UNIT / 8 : ( ( x > 0 && y > 0 && this.walls[x - 1 + y * this.sizeX - this.sizeX].indexOf( 1 ) > -1 ) ? -TILE_UNIT / 8 : 0 ), TILE_UNIT / 8 );
						ctx.lineTo( TILE_UNIT - ( walls.indexOf( 1 ) > -1 ? TILE_UNIT / 8 : ( ( x < this.sizeX - 1 && y > 0 && this.walls[x + 1 + y * this.sizeX - this.sizeX].indexOf( 3 ) > -1 ) ? -TILE_UNIT / 8 : 0 ) ), TILE_UNIT / 8 );
						break;
					case 1:
						ctx.moveTo( TILE_UNIT - TILE_UNIT / 8, walls.indexOf( 0 ) > -1 ? TILE_UNIT / 8 : ( ( x < this.sizeX - 1 && y > 0 && this.walls[x + 1 + y * this.sizeX - this.sizeX].indexOf( 2 ) > -1 ) ? -TILE_UNIT / 8 : 0 ) );
						ctx.lineTo( TILE_UNIT - TILE_UNIT / 8, TILE_UNIT - ( walls.indexOf( 2 ) > -1 ? TILE_UNIT / 8 : ( ( x < this.sizeX - 1 && y < this.sizeY - 1 && this.walls[x + 1 + y * this.sizeX + this.sizeX].indexOf( 0 ) > -1 ) ? -TILE_UNIT / 8 : 0 ) ) );
						break;
					case 2:
						ctx.moveTo( walls.indexOf( 3 ) > -1 ? TILE_UNIT / 8 : ( ( x > 0 && y < this.sizeY - 1 && this.walls[x - 1 + y * this.sizeX + this.sizeX].indexOf( 3 ) > -1 ) ? -TILE_UNIT / 8 : 0 ), TILE_UNIT - TILE_UNIT / 8 );
						ctx.lineTo( TILE_UNIT - ( walls.indexOf( 1 ) > -1 ? TILE_UNIT / 8 : ( ( x < this.sizeX - 1 && y < this.sizeY - 1 && this.walls[x + 1 + y * this.sizeX + this.sizeX].indexOf( 3 ) > -1 ) ? -TILE_UNIT / 8 : 0 ) ), TILE_UNIT - TILE_UNIT / 8 );
						break;
					case 3:
						ctx.moveTo( TILE_UNIT / 8, walls.indexOf( 0 ) > -1 ? TILE_UNIT / 8 : ( ( x > 0 && y > 0 && this.walls[x - 1 + y * this.sizeX - this.sizeX].indexOf( 2 ) > -1 ) ? -TILE_UNIT / 8 : 0 ) );
						ctx.lineTo( TILE_UNIT / 8, TILE_UNIT - ( walls.indexOf( 2 ) > -1 ? TILE_UNIT / 8 : ( ( x > 0 && y < this.sizeY - 1 && this.walls[x - 1 + y * this.sizeX + this.sizeX].indexOf( 0 ) > -1 ) ? -TILE_UNIT / 8 : 0 ) ) );
						break;
				}
			}
			ctx.stroke();
			ctx.restore();
		}
	}
	ctx.restore();
}

function Straight( doorTypes, orientation, x, y ) {
	this._dt1 = doorTypes[0];
	this._dt2 = doorTypes[1];
	this._turn = orientation;
	this._x = x;
	this._y = y;
	switch ( orientation ) {
		case ORIENTATION_0:
			break;
		case ORIENTATION_90:
			this.doors = [[0, 2]];
			this.walls = [[1, 3]];
			break;
		case ORIENTATION_180:
			this.doors = [[1, 3]];
			break;
		case ORIENTATION_270:
			this.doors = [[2, 0]];
			this.walls = [[1, 3]];
			break;
	}
	this.doorTypes = [doorTypes];
}
Straight.prototype = {
	sizeX: 1,
	sizeY: 1,
	doors: [[3, 1]],
	walls: [[0, 2]],

	draw: function(){
		var x = this._x, y = this._y;
		ctx.save();
		ctx.translate( x * TILE_UNIT + TILE_UNIT / 2, y * TILE_UNIT + TILE_UNIT / 2 );
		ctx.rotate( this._turn );
		ctx.translate( -TILE_UNIT / 2, -TILE_UNIT / 2 );

		ctx.fillStyle = doorColors[this._dt1];
		ctx.beginPath();
		ctx.moveTo( 0, 0 );
		ctx.lineTo( 0, TILE_UNIT );
		ctx.lineTo( TILE_UNIT, TILE_UNIT );
		ctx.lineTo( TILE_UNIT, 0 );
		ctx.fill();

		ctx.fillStyle = doorColors[this._dt2];
		ctx.beginPath();
		ctx.moveTo( TILE_UNIT, 0 );
		ctx.quadraticCurveTo( TILE_UNIT / 2, 0, TILE_UNIT / 2, TILE_UNIT );
		ctx.lineTo( TILE_UNIT, TILE_UNIT );
		ctx.fill();

		ctx.beginPath();
		ctx.moveTo( 0, 0 );
		ctx.lineTo( TILE_UNIT, 0 );
		ctx.moveTo( 0, TILE_UNIT );
		ctx.lineTo( TILE_UNIT, TILE_UNIT );
		ctx.stroke();
		ctx.restore();
	},

	drawBlock: function(){
		var x = this._x, y = this._y;

		ctx.save();
		ctx.translate( x * TILE_UNIT + TILE_UNIT / 2, y * TILE_UNIT + TILE_UNIT / 2 );
		ctx.rotate( this._turn );
		ctx.translate( -TILE_UNIT / 2, -TILE_UNIT / 2 );

		ctx.fillStyle = doorColors[this._dt1];
		ctx.beginPath();
		ctx.moveTo( 0, TILE_UNIT / 8 );
		ctx.lineTo( 0, TILE_UNIT - TILE_UNIT / 8 );
		ctx.lineTo( TILE_UNIT / 2, TILE_UNIT - TILE_UNIT / 8 );
		ctx.lineTo( TILE_UNIT / 2, TILE_UNIT / 8 );
		ctx.fill();

		ctx.fillStyle = doorColors[this._dt2];
		ctx.beginPath();
		ctx.moveTo( TILE_UNIT / 2, TILE_UNIT / 8 );
		ctx.lineTo( TILE_UNIT / 2, TILE_UNIT - TILE_UNIT / 8 );
		ctx.lineTo( TILE_UNIT, TILE_UNIT - TILE_UNIT / 8 );
		ctx.lineTo( TILE_UNIT, TILE_UNIT / 8 );
		ctx.fill();

		ctx.beginPath();
		ctx.moveTo( 0, TILE_UNIT / 8 );
		ctx.lineTo( TILE_UNIT, TILE_UNIT / 8 );

		ctx.moveTo( 0, TILE_UNIT - TILE_UNIT / 8 );
		ctx.lineTo( TILE_UNIT, TILE_UNIT - TILE_UNIT / 8 );
		ctx.stroke();

		ctx.restore();
	},

	build: build,
	getDoors: getDoors,
	getEnclosedSpaces: getEnclosedSpaces
};
Straight.doorOffsetDir = [[0, -1], [1, 0], [0, 1], [-1, 0]];

function Turn( doorTypes, orientation, x, y ) {
	this._dt1 = doorTypes[0];
	this._dt2 = doorTypes[1];
	this._turn = orientation;
	this._x = x;
	this._y = y;
	switch ( orientation ) {
		case ORIENTATION_0:
			this.doorTypes = [[doorTypes[0]], [], [], [doorTypes[1]]];
			this.walls = [[0, 2], [0, 1], [], [1, 3]];
			break;
		case ORIENTATION_90:
			this.doors =  [[], [0], [3], []];
			this.doorTypes = [[], [doorTypes[0]], [doorTypes[1]], []];
			this.walls = [[], [1, 3], [0, 2], [2, 3]];
			break;
		case ORIENTATION_180:
			this.doors =  [[0], [], [], [1]];
			this.doorTypes = [[doorTypes[1]], [], [], [doorTypes[0]]];
			this.walls = [[1, 3], [], [2, 3], [0, 2]];
			break;
		case ORIENTATION_270:
			this.doors =  [[], [1], [2], []];
			this.doorTypes = [[], [doorTypes[1]], [doorTypes[0]], []];
			this.walls = [[0, 3], [0, 2], [1, 3], []];
			break;
	}
}
Turn.prototype = {
	sizeX: 2,
	sizeY: 2,
	doors: [[3], [], [], [2]],

	draw: function(){
		var x = this._x, y = this._y;
		ctx.save();
		ctx.translate( x * TILE_UNIT + TILE_UNIT, y * TILE_UNIT + TILE_UNIT );
		ctx.rotate( this._turn );
		ctx.translate( -TILE_UNIT, -TILE_UNIT );

		ctx.fillStyle = doorColors[this._dt1];
		ctx.beginPath();
		ctx.moveTo( 0, 0 );
		ctx.lineTo( 0, TILE_UNIT );
		ctx.quadraticCurveTo( TILE_UNIT, TILE_UNIT, TILE_UNIT, TILE_UNIT * 2 );
		ctx.lineTo( TILE_UNIT * 2, TILE_UNIT * 2 );
		ctx.quadraticCurveTo( TILE_UNIT * 2, 0, 0, 0 );
		ctx.fill();

		ctx.fillStyle = doorColors[this._dt2];
		ctx.beginPath();
		ctx.moveTo( TILE_UNIT * Math.sqrt( 2 / 5 ), TILE_UNIT * Math.sqrt( 5 / 2 ) );
		ctx.quadraticCurveTo( TILE_UNIT, TILE_UNIT, TILE_UNIT, TILE_UNIT * 2 );
		ctx.lineTo( TILE_UNIT * 2, TILE_UNIT * 2 );
		ctx.quadraticCurveTo( TILE_UNIT * 2, TILE_UNIT, TILE_UNIT * Math.sqrt( 5 / 2 ), TILE_UNIT * Math.sqrt( 2 / 5 ) );
		ctx.fill();

		ctx.beginPath();
		ctx.moveTo( 0, 0 );
		ctx.quadraticCurveTo( TILE_UNIT * 2, 0, TILE_UNIT * 2, TILE_UNIT * 2 );
		ctx.moveTo( 0, TILE_UNIT );
		ctx.quadraticCurveTo( TILE_UNIT, TILE_UNIT, TILE_UNIT, TILE_UNIT * 2 );
		ctx.stroke();
		ctx.restore();
	},

	drawBlock: function(){
		var x = this._x, y = this._y;

		ctx.save();
		ctx.translate( x * TILE_UNIT + TILE_UNIT, y * TILE_UNIT + TILE_UNIT );
		ctx.rotate( this._turn );
		ctx.translate( -TILE_UNIT, -TILE_UNIT );

		ctx.fillStyle = doorColors[this._dt1];
		ctx.beginPath();
		ctx.moveTo( 0, TILE_UNIT / 8 );
		ctx.lineTo( TILE_UNIT * 2 - TILE_UNIT / 8 , TILE_UNIT / 8 );
		ctx.lineTo( TILE_UNIT + TILE_UNIT / 8, TILE_UNIT - TILE_UNIT / 8 );
		ctx.lineTo( 0, TILE_UNIT - TILE_UNIT / 8 );
		ctx.fill();

		ctx.fillStyle = doorColors[this._dt2];
		ctx.beginPath();
		ctx.moveTo( TILE_UNIT * 2 - TILE_UNIT / 8 , TILE_UNIT / 8 );
		ctx.lineTo( TILE_UNIT * 2 - TILE_UNIT / 8, TILE_UNIT * 2 );
		ctx.lineTo( TILE_UNIT + TILE_UNIT / 8, TILE_UNIT * 2 );
		ctx.lineTo( TILE_UNIT + TILE_UNIT / 8, TILE_UNIT - TILE_UNIT / 8 );
		ctx.fill();

		ctx.beginPath();
		ctx.moveTo( 0, TILE_UNIT / 8 );
		ctx.lineTo( TILE_UNIT * 2 - TILE_UNIT / 8 , TILE_UNIT / 8 );
		ctx.lineTo( TILE_UNIT * 2 - TILE_UNIT / 8 , TILE_UNIT * 2 );

		ctx.moveTo( 0, TILE_UNIT - TILE_UNIT / 8 );
		ctx.lineTo( TILE_UNIT + TILE_UNIT / 8, TILE_UNIT - TILE_UNIT / 8 );
		ctx.lineTo( TILE_UNIT + TILE_UNIT / 8, TILE_UNIT * 2 );
		ctx.stroke();

		ctx.restore();
	},

	build: build,
	getDoors: getDoors,
	getEnclosedSpaces: getEnclosedSpaces
};
Turn.doorOffsetDir = [[0, -2], [1, 0], [-1, 1], [-2, -1], [-1, -2], [1, -1], [0, 1], [-2, 0]];

function Three( doorTypes, orientation, x, y ) {
	this._dt1 = doorTypes[0];
	this._dt2 = doorTypes[1];
	this._dt3 = doorTypes[2];
	this._turn = orientation;
	this._x = x;
	this._y = y;
	switch ( orientation ) {
		case ORIENTATION_0:
			this.doorTypes = [[doorTypes[0]], [], [], [doorTypes[1]]];
			break;
		case ORIENTATION_90:
			this.doors =  [[], [0], [3], []];
			this.doorTypes = [[], [doorTypes[0]], [doorTypes[1]], []];
			break;
		case ORIENTATION_180:
			this.doors =  [[0], [], [], [1]];
			this.doorTypes = [[doorTypes[1]], [], [], [doorTypes[0]]];
			break;
		case ORIENTATION_270:
			this.doors =  [[], [1], [2], []];
			this.doorTypes = [[], [doorTypes[1]], [doorTypes[0]], []];
			break;
	}
}
Three.prototype = {
	sizeX: 3,
	sizeY: 2,
	doors: [[3], [], [],
			[], [2], []],

	draw: draw,
	drawBlock: drawBlock,
	build: build,
	getDoors: getDoors,
	getEnclosedSpaces: getEnclosedSpaces
};
Turn.doorOffsetDir = [[0, -2], [1, 0], [-1, 1], [-2, -1], [-1, -2], [1, -1], [0, 1], [-2, 0]];

function Start( x, y ) {
	this._x = x;
	this._y = y;
}
Start.prototype = {
	sizeX: 3,
	sizeY: 4,
	doors: [[], [0], [],
			[3], [], [1],
			[], [], [],
			[], [], []],
	doorTypes: [[], [DOOR_CAVE], [],
			[DOOR_CAVE], [], [DOOR_CAVE],
			[], [], [],
			[], [], []],

	walls: [[], [1, 3], [],
			[0, 2], [], [0, 2],
			[], [1, 3], [],
			[], [1, 2, 3], []],

	draw: draw,
	drawBlock: drawBlock,

	build: build,
	getDoors: getDoors,
	getEnclosedSpaces: getEnclosedSpaces
};

var _tiles = [new Start( 20, 50 )];

for ( var i = 0; i < _tiles.length; i++ ) {
	if ( TileAllowed( _tiles[i] ) ) {
		tiles.push( _tiles[i] );
	}
}
redrawAll( true );

document.getElementsByTagName( 'button' )[0].onclick = function(){
	for ( var i = tiles.length - 1; i >= 0; i-- ) {
		var tile = tiles[i].build();
		if ( tile ) {
			tiles.push( tile );
			redrawAll();
			return;
		}
	}
	alert( 'Nope.avi' );
};
document.getElementsByTagName( 'button' )[1].onclick = function(){
	redrawAll( true );
};

document.getElementsByTagName( 'button' )[2].onclick = function(){
	var orig = tiles.slice( 0 ), optimal = [], iter = 20;

	setTimeout( function a() {
		if ( iter-- ) {
			if ( optimal.length < tiles.length )
				optimal = tiles.slice( 0 );
			tiles = orig.slice( 0 );
			
			setTimeout( function b() {
				var keepGoing = true;
				for ( var i = tiles.length - 1; i >= 0; i-- ) {
					var tile = tiles[i].build();
					if ( tile ) {
						tiles.push( tile );
						keepGoing = true;
						break;
					} else {
						keepGoing = false;
					}
				}
				redrawAll();
				setTimeout( keepGoing ? b : a, 1 );
			}, 1 );
		} else {
			tiles = optimal;
			redrawAll( true );
		}
	}, 1 );
};