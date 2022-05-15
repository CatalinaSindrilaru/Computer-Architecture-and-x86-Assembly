// Copyright Sindrilaru Catalina-Maria, 312CA, 2022

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structs.h"
#include <inttypes.h>

#define MAX_STRING 256
#define DIE(assertion, call_description)                    \
    do {                                    				\
        if (assertion) {                       			    \
            fprintf(stderr, "(%s, %s, %d): ",               \
                    __FILE__, __FUNCTION__, __LINE__);      \
            perror(call_description);                       \
            exit(EXIT_FAILURE);                             \
        }                                                   \
    } while (0)

void fill_data(data_structure *data);
int add_last(void **arr, int *len, data_structure *data);
int add_at(void **arr, int *len, data_structure *data, int index);
int delete_at(void **arr, int *len, int index);
void find_index(void *data_block, int len, int index);
void print_all(void *arr, int len);

int main() 
{
	// the vector of bytes u have to work with
	// good luck :)

	void *arr = NULL;
	int len = 0;


	char *command;
	command = malloc(MAX_STRING * sizeof(char));
	DIE(!command, "Malloc failed at command\n");

	data_structure *data;
	data = malloc(sizeof(data_structure));
	DIE(!data, "Malloc failed at data\n");

	int index;
	while(1) {
		scanf("%s", command);
	
		if (strcmp(command, "insert") == 0) {
			fill_data(data);
			add_last(&arr, &len, data);
        } else if (strcmp(command, "insert_at") == 0) {
            scanf("%d", &index);
            fill_data(data);
            add_at(&arr, &len, data, index);

        }  else if (strcmp(command, "delete_at") == 0) {
            scanf("%d", &index);
            delete_at(&arr, &len, index);

        } else if (strcmp(command, "find") == 0) {
            scanf("%d", &index);
            find_index(arr, len, index);

	    } else if (strcmp(command, "print") == 0) {
            print_all(arr, len);
    
        } else if (strcmp(command, "exit") == 0) {
            free(arr);
            break;
        }   
	}

    free(data);
	free(command);

	return 0;
}


/* Citeste datele de intrare si le stocheaza in structura data*/
void fill_data(data_structure *data)
{
    int type, total_len;
    scanf("%d", &type);

    char *name1, *name2;
    name1 = malloc(MAX_STRING * sizeof(char));
	DIE(!name1, "Malloc failed at name1\n");
    name2 = malloc(MAX_STRING * sizeof(char));
	DIE(!name2, "Malloc failed at name2\n");

    /* Aloc data->header si salvez tipul dedicatiei */
    data->header = malloc(sizeof(head));
	DIE(!(data->header), "Malloc failed at data->header\n");
    data->header->type = (unsigned char)type;

    /* Modalitatea de stocare pentru primul tip este valabila si pentru celelalte doua tipuri,
    difera doar tipurile de int ale bancnotelor (int8_t/ int16_t/ int32_t) */
    if (type == 1) {
        int8_t bill1;
	    int8_t bill2;
    
		scanf("%s%hhd%hhd%s", name1, &bill1, &bill2, name2);

        /* Calculez lungimea in octeti ocupata de datele citite, luand in considerare
        '\0' de la finalul fiecarui nume citit */
        total_len = strlen(name1) + 1 + strlen(name2) + 1 + 2 * sizeof(int8_t);
    
        /* Salvez lungimea*/
        data->header->len = (unsigned int)total_len;
    
        data->data = malloc(data->header->len * sizeof(char));
    	DIE(!(data->data), "Malloc failed at data->data\n");
    
        /* Copiez pe rand primul nume citit, cele doua numere, apoi celalt nume, intr-o
        zona continua de memorie, tinand mereu cont unde am ramas*/
        int curr_pos = 0;
        memcpy(data->data + curr_pos, name1, strlen(name1) + 1);
        curr_pos += strlen(name1) + 1;
        memcpy(data->data + curr_pos , &bill1, sizeof(int8_t));
        curr_pos += sizeof(int8_t);
        memcpy(data->data + curr_pos, &bill2, sizeof(int8_t));
        curr_pos += sizeof(int8_t);
        memcpy(data->data + curr_pos, name2, strlen(name2) + 1);

    } else if (type == 2) {
        int16_t bill1;
	    int32_t bill2;

		scanf("%s%hd%d%s", name1, &bill1, &bill2, name2);

        total_len = strlen(name1) + 1 + strlen(name2) + 1 + sizeof(int16_t) + sizeof(int32_t);
        data->header->len = (unsigned int)total_len;

        data->data = malloc(data->header->len * sizeof(char));
    	DIE(!(data->data), "Malloc failed at data->data\n");

        int curr_pos = 0;
        memcpy(data->data + curr_pos, name1, strlen(name1) + 1);
        curr_pos += strlen(name1) + 1;
        memcpy(data->data + curr_pos , &bill1, sizeof(int16_t));
        curr_pos += sizeof(int16_t);
        memcpy(data->data + curr_pos, &bill2, sizeof(int32_t));
        curr_pos += sizeof(int32_t);
        memcpy(data->data + curr_pos, name2, strlen(name2) + 1);

    } else if (type == 3) {
        int32_t bill1;
	    int32_t bill2;

		scanf("%s%d%d%s", name1, &bill1, &bill2, name2);
        total_len = strlen(name1) + 1 + strlen(name2) + 1 + sizeof(int32_t) + sizeof(int32_t);

        data->header->len = (unsigned int)total_len;
    
        data->data = malloc(data->header->len * sizeof(char));
     	DIE(!(data->data), "Malloc failed at data->data\n");

        int curr_pos = 0;
        memcpy(data->data + curr_pos, name1, strlen(name1) + 1);
        curr_pos += strlen(name1) + 1;
        memcpy(data->data + curr_pos , &bill1, sizeof(int32_t));
        curr_pos += sizeof(int32_t);
        memcpy(data->data + curr_pos, &bill2, sizeof(int32_t));
        curr_pos += sizeof(int32_t);
        memcpy(data->data + curr_pos, name2, strlen(name2) + 1);       
    }

    free(name1);
    free(name2);
}

int add_last(void **arr, int *len, data_structure *data)
{
    int curr_pos = 0; /* Retine pozitia la care pot adauga in arr */
    if (*len == 0) {
        /* In cazul in care nu am stocat nimic in arr pana acum, alocam memorie pentru
        datele din structura data*/
        *arr = malloc(sizeof(unsigned char) + sizeof(unsigned int) + (int)data->header->len);
        DIE(!(*arr), "Malloc failed at arr\n");
    } else {
        void *aux = *arr;

        /* Parcurg vectorul arr pentru a vedea cati octeti are in total*/
        for (int i = 0; i < *len; i++) {
            unsigned char type = *((unsigned char *)(aux + curr_pos));
            if (type != 1 && type != 2 && type != 3) {
                return -1;
            }
            curr_pos += sizeof(unsigned char);
            unsigned int len_data = *((unsigned int *)(aux + curr_pos));
 
            curr_pos += sizeof(unsigned int) + len_data;
        }

        /* Realoc arr cu numarul de octeti pe care ii contine plus cati octeti ocupa datele
        din structura pe care vreau sa o adaug*/
        *arr = realloc(*arr, curr_pos + sizeof(unsigned char) + sizeof(unsigned int) + data->header->len);
        DIE(!(*arr), "Realloc failed at arr\n");
    }

    int bytes_copied = 0; /* Contor ce retine cati octeti am adaugat deja din stuctura data */

    /* Copiez mai intai valorile din header, iar apoi datele propriu-size*/
    memcpy(*arr + curr_pos, &(data->header->type), sizeof(data->header->type));
    bytes_copied += sizeof(data->header->type);

    memcpy(*arr + curr_pos + bytes_copied, &(data->header->len), sizeof(data->header->len));
    bytes_copied += sizeof(data->header->len);

    memcpy(*arr + curr_pos + bytes_copied, data->data, data->header->len);

    free(data->header);
    free(data->data);

    /* Cresc numarul de elemente din vectorul arr*/
    *len += 1;

    return 0;
}

int add_at(void **arr, int *len, data_structure *data, int index)
{
    if (index < 0) {
        return -1;
    }

    int total_len_arr = 0, pos_before_index;
    void *aux = *arr;

    /* Calculez numarul total de octeti pe care ii are arr*/
    for (int i = 0; i < *len; i++) {
        unsigned char type = *((unsigned char *)(aux + total_len_arr));
        if (type != 1 && type != 2 && type != 3) {
            return -1;
        }
        total_len_arr += sizeof(unsigned char);
        unsigned int len_data = *((unsigned int *)(aux + total_len_arr));
        total_len_arr += sizeof(unsigned int) + len_data;

        /* Retin cati octeti sunt in arr inainte de elementul cu indexul dat*/
        if (i == index - 1) {
            pos_before_index = total_len_arr;
        }
    }

    /* Calculez numarul de octeti pe care ii va avea arr dupa adaugarea noilor date*/
    int total_size;
    total_size = sizeof(unsigned char) + sizeof(unsigned int) + (int)data->header->len + total_len_arr;

    /* Aloc un vector cu noua dimensiune in care voi copia datele din vechiul vector plus noile date,
    dar pe pozitia dorita*/
    void *copy;
    copy = malloc(total_size * sizeof(char));
    DIE(!copy, "Malloc failed at copy\n");

    if (index == 0) { /* Daca vreau sa inserez datele la inceputul zone de memorie*/
        int bytes_copied = 0;
        /* Copiez datele din noua structura la inceput la inceput*/
        memcpy(copy, &(data->header->type), sizeof(data->header->type));
        bytes_copied += sizeof(data->header->type);
        memcpy(copy + bytes_copied, &(data->header->len), sizeof(data->header->len));
        bytes_copied += sizeof(data->header->len);
        memcpy(copy + bytes_copied, data->data, data->header->len);
        /* Adaug apoi la sfarsit toate datele ce se aflau in vectorul initial */
        memcpy(copy + total_size - total_len_arr, *arr, total_len_arr);
    
    } else if (index >= *len) {
        /* Copiez mai intai toate datele din vectorul initial*/
        memcpy(copy, *arr, total_len_arr);
        /* Apoi copiez datele din noua structura*/
        memcpy(copy + total_len_arr, &(data->header->type), sizeof(data->header->type));
        total_len_arr += sizeof(data->header->type);
        memcpy(copy + total_len_arr, &(data->header->len), sizeof(data->header->len));
        total_len_arr += sizeof(data->header->len);
        memcpy(copy + total_len_arr, data->data, data->header->len);
        total_len_arr += data->header->len;
        
    } else {
        /* Copiez toate datele ce se afla inainte de pozitia la care vreau sa inserez*/
        memcpy(copy, *arr, pos_before_index);
        int bytes_copied = 0;
        /* Copiez datele din noua stuctura*/
        memcpy(copy + pos_before_index, &(data->header->type), sizeof(data->header->type));
        bytes_copied += sizeof(data->header->type);
        memcpy(copy + pos_before_index + bytes_copied, &(data->header->len), sizeof(data->header->len));
        bytes_copied += sizeof(data->header->len);
        memcpy(copy + pos_before_index + bytes_copied, data->data, data->header->len);
        bytes_copied += data->header->len;
        /* Copiez datele ce au ramas in vectorul initial (ce se aflau dupa pozitia la care voiam sa inserez)*/
        memcpy(copy + pos_before_index + bytes_copied, *arr + pos_before_index, total_len_arr - pos_before_index);
    }

    free(*arr);
    *arr = copy;

    free(data->header);
    free(data->data);

    /* Cresc numarul de elemente din vector*/
    *len += 1;

    return 0;
}

int delete_at(void **arr, int *len, int index)
{
    void *aux = *arr;
    int total_len_arr = 0; /* Stochez numarul total de octeti din vector*/
    int pos_before_index; /* Stochez la ce octet incepe elementul cu indexul dat */
    int pos_after_index; /* Stochez la ce octet se termina elementul cu indexul dat */
    int len_arr_without_last; /* Stochez numarul octetilor din vector, fara ultimul element*/

    for (int i = 0; i < *len; i++) { 
        unsigned char type = *((unsigned char *)(aux + total_len_arr));
        if (type != 1 && type != 2 && type != 3) {
            return -1;
        }
        total_len_arr += sizeof(unsigned char);
        unsigned int len_data = *((unsigned int *)(aux + total_len_arr));
        total_len_arr += sizeof(unsigned int) + len_data;

        if (i == index - 1) {
            pos_before_index = total_len_arr;
        }

        if (i == index) {
            pos_after_index = total_len_arr;
        }

        if (i == *len - 1) {
            len_arr_without_last = total_len_arr;
        }
    }
    /* Verific daca stergerea se face de la inceput, de la final sau din interior */
    if (index == 0) {

        /* Stochez in curr_pos cati octeti are prima stuctura din arr*/
        int curr_pos = 0;
        unsigned char type = *((unsigned char *)(aux + curr_pos));
        if (type != 1 && type != 2 && type != 3) {
            return -1;
        }
        curr_pos += sizeof(unsigned char);
        unsigned int len_data = *((unsigned int *)(aux + curr_pos));
        curr_pos += sizeof(unsigned int) + len_data;

        /* Aloc un nou vector in care voi copia datele din vectorul initial, sarind peste
        primul element(structura) */
        void *copy;
        copy = malloc((total_len_arr - curr_pos) * sizeof(char));
        DIE(!copy, "Malloc failed at copy\n");
        memcpy(copy, *arr + curr_pos, total_len_arr - curr_pos);

        free(*arr);
        *arr = copy;
        *len -= 1;

    } else if (index == *len - 1) {
        /* Aloc si copiez in noul vector datele din vectorul initial, dara datele ultimului element */
        void *copy;
        copy = malloc(len_arr_without_last);
        memcpy(copy, *arr, len_arr_without_last);
        DIE(!copy, "Malloc failed at copy\n");

        free(*arr);
        *arr = copy;
        *len -= 1;

    } else {

        /* Calculez cati octeti are elementul(structura) pe care vreau sa il/o sterg*/
        int wiped_bytes = pos_after_index - pos_before_index;
        void *copy;
        copy = malloc((total_len_arr - wiped_bytes) * sizeof(char));
        DIE(!copy, "Malloc failed at copy\n");

        /* Copiez datele de dinainte de elementul cu indexul dat, sarind peste el, apoi pe cele de dupa*/
        memcpy(copy, *arr, pos_before_index);
        memcpy(copy + pos_before_index, *arr + pos_after_index, total_len_arr - pos_after_index);

        free(*arr);
        *arr = copy;
        *len -= 1;

    }

    return 0;
}

void find_index(void *data_block, int len, int index) 
{
    if (index < 0 || index >= len) {
        return;
    }

    void *aux = data_block;
    int curr_pos = 0;

    /* Aflu octetul unde se afla elementul cu indexul dat din vector*/
    for (int i = 0; i < index; i++) { 
        unsigned char type = *((unsigned char *)(aux + curr_pos));
        if (type != 1 && type != 2 && type != 3) {
            return;
        }
        curr_pos += sizeof(unsigned char);
        unsigned int len_data = *((unsigned int *)(aux + curr_pos));
        curr_pos += sizeof(unsigned int) + len_data;
    } 

    /* Citesc tipul si lungimea datelor pe care urmeaza sa le citesc*/
    unsigned char type = *((unsigned char *)(aux + curr_pos));
    curr_pos += sizeof(unsigned char);

    unsigned int len_data = *((unsigned int *)(aux + curr_pos));
    curr_pos += sizeof(unsigned int);

    char ch;
    int bytes_copied = 0;
    aux = data_block;
    int ok = 0;
    char *name1;
    
    /* Retin unde se termina primul nume, cautand unde se afla '\0' */
    while (ok == 0) {
        ch = *((char *)(aux + curr_pos + bytes_copied));
        bytes_copied++;
        if (ch == 0) {
            /* Cand ajung la finalul numelui, il copiez in name1*/
            name1 = malloc(bytes_copied);
            DIE(!name1, "Malloc failed at name1\n");
            memcpy(name1, aux + curr_pos, bytes_copied);
            ok = 1;
        }
    }

    int len_name1 = bytes_copied;
    curr_pos += bytes_copied;

    int len_bills;
    /* Citesc numerele tinand cont de tipul dedicatiei. Citirea si afisarea lor se face
    in acelasi mod, ceea ce difera este tipul int-ului*/
    if (type == 1) {
        int8_t bill1;
	    int8_t bill2;

        /* Calculez cati octeti ocupa cele doua numere*/
        len_bills = 2 * sizeof(int8_t);
        /* Citesc numerele*/
        bill1 = *((int8_t *)(aux + curr_pos));
        curr_pos += sizeof(int8_t);
        bill2 = *((int8_t *)(aux + curr_pos));
        curr_pos += sizeof(int8_t); 

        /* Stiind cati octeti ocupa datele propriu zise, dar si primul nume si numerele citite mai sus, pot
        calcula cat ocupa cel de-al doilea nume*/
        int len_name2 = len_data - len_bills - len_name1;
        /* Aloc si citesc al doilea nume*/
        char *name2 = malloc(len_name2);
        DIE(!name2, "Malloc failed at name2\n");
        memcpy(name2, aux + curr_pos, len_name2);

        /* Afisez datele corespunzatoare unui element in formatul dorit*/
        printf("Tipul %u\n", type);
        printf("%s pentru %s\n", name1, name2);
        printf("%"PRId8"\n", bill1);
        printf("%"PRId8"\n", bill2);

        free(name2);

    } else if (type == 2) {
        int16_t bill1;
	    int32_t bill2;

        len_bills = sizeof(int16_t) + sizeof(int32_t); 
        bill1 = *((int16_t *)(aux + curr_pos));
        curr_pos += sizeof(int16_t);
        bill2 = *((int32_t *)(aux + curr_pos));
        curr_pos += sizeof(int32_t); 

        int len_name2 = len_data - len_bills - len_name1;
        char *name2 = malloc(len_name2);
        DIE(!name2, "Malloc failed at name2\n");
        memcpy(name2, aux + curr_pos, len_name2);

        printf("Tipul %u\n", type);
        printf("%s pentru %s\n", name1, name2);
        printf("%"PRId16"\n", bill1);
        printf("%"PRId32"\n", bill2);

        free(name2);

    } else if (type == 3) {
        int32_t bill1;
	    int32_t bill2;

        len_bills = 2 * sizeof(int32_t);
        bill1 = *((int32_t *)(aux + curr_pos));
        curr_pos += sizeof(int32_t);
        bill2 = *((int32_t *)(aux + curr_pos));
        curr_pos += sizeof(int32_t); 

        int len_name2 = len_data - len_bills - len_name1;
        char *name2 = malloc(len_name2);
        DIE(!name2, "Malloc failed at name2\n");
        memcpy(name2, aux + curr_pos, len_name2);

        printf("Tipul %u\n", type);
        printf("%s pentru %s\n", name1, name2);
        printf("%"PRId32"\n", bill1);
        printf("%"PRId32"\n", bill2);

        free(name2);
    }

    printf("\n");

    free(name1);
}

void print_all(void *arr, int len)
{
    for (int i = 0; i < len; i++) {
        find_index(arr, len, i);
    }
}
