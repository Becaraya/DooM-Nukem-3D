// Fonction pour obtenir le chiffre des dixièmes d'un nombre
function grepTenth(n) {
	const tmp = Math.floor(n);
	return Math.floor((n - tmp) * 10).toString();
  }
  
  // Fonction pour convertir un nombre flottant en chaîne de caractères
  function dtoaDoom(n) {
	if (n > Number.MAX_SAFE_INTEGER) {
	  return null;
	}
  
	const integerPart = Math.floor(n).toString(); // Partie entière
	const decimalPart = grepTenth(n) + grepTenth(n * 10); // Deux chiffres après la virgule
  
	return `${integerPart}.${decimalPart}`;
  }