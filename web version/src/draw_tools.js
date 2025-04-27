// Fonction pour dessiner un triangle
function drawTriangle(ctx, p, i, color) {
	let a = { x: p.x, y: p.y - 8 };
	while (a.y <= p.y + 8) {
	  const b = { x: a.x + i, y: a.y };
	  if (i > 0) {
		i += a.y >= p.y ? -1 : 1;
	  } else {
		i -= a.y >= p.y ? -1 : 1;
	  }
	  putLine(ctx, a, b, color); // Dessine une ligne entre deux points
	  a.y++;
	}
  }
  
  // Fonction pour dessiner une ligne entre deux points
  function putLine(ctx, a, b, color) {
	const delta = { x: Math.abs(b.x - a.x), y: Math.abs(b.y - a.y) };
	const sign = { x: a.x < b.x ? 1 : -1, y: a.y < b.y ? 1 : -1 };
	let error = delta.x - delta.y;
	let cur = { ...a };
  
	ctx.fillStyle = `#${color.toString(16).padStart(6, '0')}`;
	while (cur.x !== b.x || cur.y !== b.y) {
	  ctx.fillRect(cur.x, cur.y, 1, 1); // Dessine un pixel
	  const error2 = error * 2;
	  if (error2 > -delta.y) {
		error -= delta.y;
		cur.x += sign.x;
	  }
	  if (error2 < delta.x) {
		error += delta.x;
		cur.y += sign.y;
	  }
	}
  }
  
  // Fonction pour dessiner un rectangle
  function putRectangle(ctx, a, b, color) {
	const c = { x: a.x, y: b.y };
	const d = { x: b.x, y: a.y };
  
	putLine(ctx, a, d, color); // Ligne supérieure
	putLine(ctx, a, c, color); // Ligne gauche
	putLine(ctx, d, b, color); // Ligne inférieure
	putLine(ctx, b, c, color); // Ligne droite
  }