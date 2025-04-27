// Constantes nécessaires
const D_2PI = 8192; // 2 * PI en unités discrètes
const D_2PIM = D_2PI - 1; // Masque pour limiter les angles dans [0, 2*PI)

// Fonction pour ajouter deux angles
function addAngle(a1, a2) {
  return (a1 + a2) & D_2PIM; // Addition des angles avec masquage
}

// Fonction pour soustraire deux angles
function subAngle(a1, a2) {
  if (a1 >= a2) {
    return (a1 - a2) & D_2PIM; // Soustraction avec masquage si a1 >= a2
  }
  return D_2PI - ((a2 - a1) & D_2PIM); // Calcul complémentaire si a1 < a2
}