#ifndef MYSTRING_H
#define MYSTRING_H

/**
\def MYSTRING_DEFAULT_CAPACITY 
Capcite par defaut d'une chaine
*/
#define MYSTRING_DEFAULT_CAPACITY 10

typedef struct mystring string;

/**
 * \struct mystring
 * \brief Objet chaîne de caracteres.
 *
 * mystring est un petit objet de gestion de chaînes de caractères. 
 * La chaîne se termine obligatoirement par un zéro de fin et l'objet 
 * connait la taille de chaîne contient !
 */

struct mystring
{
  char* ptr;
  int capacity;
  int size;
};

/*
========================
INTERFACE PUBLIQUE : 
========================
*/

/*
========================
Construction/Destruction
========================
*/
/**
 * \brief Fonction permettant d'initialiser le contenu de la structure. L'espace memoire (ie s) ne doit pas etre NULL
 
    A la sortie, s->ptr est valide, s->capacity=MYSTRING_DEFAULT_CAPACITY et s->size=0
 */
void build_string(string* s);

/**
  \brief Fonction permettant de liberer le contenu de la structure. L'espace memoire (ie s) ne doit pas etre NULL
 
 A la sortie, s->ptr est invalide, s->capacity=0 et s->size=0. 
 L'espace mémoire que la structure en elle meme occupe doit encore etre libere s'il a ete alloue dynamiquement
 */
void destruct_string(string* s);

/*
========================
Consultation
========================
*/


/**
 * \brief Fonction retournant la taille de la chaine de caractere. Complexité O(1)
 */
int size(string s);

/**
 * \brief Fonction retournant la capacité de stockage de la chaine de caractere. Complexité O(1)
 */
int capacity(string s);

/**
 * \fn const char* str(string s)
 * \brief Fonction permettant un accès a la representation sous jacente de la chaine contenue dans s
 */
const char* get_str(string s);

/*
========================
MODIFICATION
========================
*/


/**
 * \fn void append(string* s,const char* c)
 * \brief Fonction permetant d'ajouter a la chaine s la chaine pointé par c. s et c ne doivent pas etre nuls.
 */
void append_string(string* s,const char* c);

/**
 * \fn reserve(string* s,int new_capa)
 * \brief Fonction permetant d'agrandir la capcite de stockage de s a la valeur new_capa. 
 
   new_capa ne doit pas valoir 0 (sinon s->ptr devient invalide) mais peut inferieur a la valeur avant appel de la capacite
 */
void reserve(string* s,int new_capa);

/**
 * \fn print_string(string s)
 * \brief Fonction permettant d'afficher a l'ecran la chaine s.
 */
void print_string(string s);

/**
 * \fn pop_string(string* s)
 * \brief Fonction permettant de retirer le dernier caractere de la chaine. s ne doit pas etre null
 */
void pop_string(string* s);

/**
 * \fn stringify_int(int i)
 * \brief Fonction permettant de transformer l'int fourni en paramètre en une chaine de caractère C. L'espace mémoire renvoyé doit être libéré après utilisation.
*/
char* stringify_int(int i);
#endif

/*
test "unitaire" de mystring: 
  string s;
  build_string(&s);
  append(&s,"c");
  append(&s,"o");
  append(&s,"u");
  append(&s,"c");
  append(&s,"o");
  append(&s,"u");
  append(&s," du con !");
  print_string(s);

  pop_string(&s);
  print_string(s);

  pop_string(&s);
  print_string(s);

  destruct_string(&s);
*/
