/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rkhelif <rkhelif@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 15:10:08 by rkhelif           #+#    #+#             */
/*   Updated: 2020/08/25 21:37:57 by rkhelif          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

/**
 * @file ft_split.c
 * 
*/

/**
 * @brief Compare deux chaînes de caractères.
 * 
 * @param str La première chaîne de caractères.
 * @param charset La deuxième chaîne de caractères.
 * @param i L'index de départ de la comparaison dans charset.
 * @return Le nombre de caractères identiques si les chaînes sont identiques jusqu'à la fin de charset, 0 sinon.
 */
int		ft_strncmp(char *str, char *charset, int i)
{
	while (charset[++i])
		if (charset[i] != str[i])
			return (0);
	return (i);
}

/**
 * @brief Compte le nombre de lignes dans une chaîne de caractères, en utilisant un séparateur.
 * 
 * @param str La chaîne de caractères à analyser.
 * @param charset La chaîne de caractères séparateur.
 * @param i L'index de départ dans str.
 * @param j Un indicateur pour savoir si un séparateur a été trouvé.
 * @return Le nombre de lignes dans la chaîne de caractères.
 */
int		ft_line(char *str, char *charset, int i, int j)
{
	int	nbr;

	nbr = 0;
	while (str[i] == charset[0] && (ft_strncmp(str + i, charset, -1) > 0))
		i += ft_strncmp(str + i, charset, -1);
	nbr = (str[i] != '\0') ? nbr + 1 : nbr;
	while (str[i])
	{
		while (str[i] == charset[0] &&
		(ft_strncmp(str + i, charset, -1) > 0) && ++j != 0)
			i += ft_strncmp(str + i, charset, -1);
		(j > 0 && str[i] != '\0') ? nbr++ : 0;
		j = 0;
		i = (str[i] == '\0') ? i : i + 1;
	}
	return (nbr);
}

/**
 * @brief Alloue de la mémoire pour une ligne de la chaîne de caractères.
 * 
 * @param str La chaîne de caractères à analyser.
 * @param charset La chaîne de caractères séparateur.
 * @param tab La ligne de la chaîne de caractères.
 * @param i L'index de départ dans str.
 * @return Un pointeur vers la mémoire allouée, ou NULL en cas d'erreur.
 */
char	*ft_put_malloc(char *str, char *charset, char *tab, int i)
{
	int	k;
	int	x;

	x = 0;
	while (str[i] == charset[0] && (ft_strncmp(str + i, charset, -1) > 0))
		i += ft_strncmp(str + i, charset, -1);
	k = i;
	while (str[i] && x == 0)
	{
		if (str[i] == charset[0] && (ft_strncmp(str + i, charset, -1) > 0))
			x = 1;
		(x == 0) ? i++ : 0;
	}
	if ((tab = malloc(sizeof(charset[0]) * ((i - k) + 1))) == NULL)
		return (NULL);
	return (tab);
}

/**
 * @brief Copie une ligne de la chaîne de caractères dans la mémoire allouée.
 * 
 * @param str La chaîne de caractères à analyser.
 * @param charset La chaîne de caractères séparateur.
 * @param tab La ligne de la chaîne de caractères.
 * @param i L'index de départ dans str.
 * @return L'index de la fin de la ligne dans str.
 */
int		ft_put_in_tab(char *str, char *charset, char *tab, int i)
{
	int	k;
	int	x;

	x = 0;
	k = -1;
	while (str[i] == charset[0] && (ft_strncmp(str + i, charset, -1) > 0))
		i += ft_strncmp(str + i, charset, -1);
	while (str[i] && x == 0)
	{
		if (str[i] == charset[0] && (ft_strncmp(str + i, charset, -1) > 0))
			x = 1;
		if (x == 0)
			tab[++k] = str[i];
		(x == 0) ? i++ : 0;
	}
	tab[++k] = '\0';
	return (i);
}

/**
 * @brief Divise une chaîne de caractères en un tableau de chaînes de caractères, en utilisant un séparateur.
 * 
 * @param str La chaîne de caractères à diviser.
 * @param charset La chaîne de caractères séparateur.
 * @return Un tableau de chaînes de caractères, ou NULL en cas d'erreur.
 */
char	**ft_split(char *str, char *charset)
{
	char	**tab;
	int		nbr_line;
	int		i;
	int		j;

	j = -1;
	tab = NULL;
	i = 0;
	nbr_line = ft_line(str, charset, 0, 0);
	if ((tab = malloc(sizeof(tab[0]) * (nbr_line + 1))) == NULL)
		return (NULL);
	while (++j < nbr_line)
	{
		if ((tab[j] = ft_put_malloc(str + i, charset, tab[j], 0)) == NULL)
			return (NULL);
		i += ft_put_in_tab(str + i, charset, tab[j], 0);
	}
	tab[nbr_line] = 0;
	return (tab);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akerloc- <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 17:31:51 by akerloc-          #+#    #+#             */
/*   Updated: 2019/10/07 17:41:11 by akerloc-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

/**
 * @file ft_atoi.c
 * @brief Implémentation de la fonction ft_atoi.
 */

/**
 * @brief Vérifie si un caractère est un caractère d'espacement.
 * 
 * @param c Le caractère à vérifier.
 * @return 1 si le caractère est un caractère d'espacement, 0 sinon.
 */
static int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v' ||
	c == '\f' || c == '\r' || c == ' ')
		return (1);
	else
		return (0);
}

/**
 * @brief Convertit une chaîne de caractères en entier.
 * 
 * @param str La chaîne de caractères à convertir.
 * @return L'entier converti.
 */
int			ft_atoi(const char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (str[i] > 47 && str[i] < 58 && str[i] != '\0')
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res * sign);
}

/**
 * @file philo_one.h
 * @brief Contient les déclarations pour le projet Philosophes (philo_one).
 */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <string.h>
# include <unistd.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>

/**
 * @struct s_bin
 * @brief Structure contenant les variables globales du programme.
 */
struct s_bin;

/**
 * @struct s_node
 * @brief Structure représentant un philosophe.
 */
typedef struct		s_node
{
	int				value; /**< Valeur du philosophe. */
	pthread_mutex_t	*lock_std; /**< Mutex pour l'affichage standard. */
	pthread_mutex_t	lock; /**< Mutex pour le philosophe. */
	pthread_mutex_t	eat; /**< Mutex pour l'action de manger. */
	int				end; /**< Indicateur de fin du programme. */
	int				tt_die; /**< Temps de mourir. */
	int				tt_eat; /**< Temps pour manger. */
	int				tt_sleep; /**< Temps pour dormir. */
	long long		start; /**< Temps de départ. */
	int				count_eat; /**< Nombre de fois que le philosophe a mangé. */
	int				nb_eat; /**< Nombre de fois que le philosophe doit manger. */
	pthread_t		thread; /**< Thread du philosophe. */
	pthread_t		monitor; /**< Thread de surveillance du philosophe. */
	struct s_node	*next; /**< Pointeur vers le philosophe suivant. */
	char			str[50]; /**< Chaîne de caractères pour l'affichage. */
	struct s_bin	*var; /**< Pointeur vers les variables globales. */
}					t_node;

/**
 * @struct s_bin
 * @brief Structure contenant les variables globales du programme.
 */
typedef struct		s_bin
{
	int				time_to_die; /**< Temps de mourir. */
	int				time_to_eat; /**< Temps pour manger. */
	int				time_to_sleep; /**< Temps pour dormir. */
	int				nb_eat; /**< Nombre de fois que chaque philosophe doit manger. */
	int				nb; /**< Nombre de philosophes. */
	int				end; /**< Indicateur de fin du programme. */
	t_node			*philo; /**< Pointeur vers le premier philosophe. */
	int				count_eat; /**< Nombre total de fois que les philosophes ont mangé. */
	pthread_mutex_t	lock_std; /**< Mutex pour l'affichage standard. */
}					t_bin;

/**
 * @brief Met en pause le programme pendant un temps donné.
 * 
 * @param n Le temps de pause en millisecondes.
 */
void				ft_sleep(int n);

/**
 * @brief Calcule la longueur d'une chaîne de caractères.
 * 
 * @param str La chaîne de caractères.
 * @return La longueur de la chaîne de caractères.
 */
size_t				ft_strlen(const char *str);

/**
 * @brief Affiche une chaîne de caractères sur la sortie standard.
 * 
 * @param s La chaîne de caractères à afficher.
 * @param fd Le descripteur de fichier de la sortie standard (généralement 1).
 */
void				ft_putstr_fd(char *s, int fd);

/**
 * @brief Affiche un nombre long long sur la sortie standard, suivi d'un retour à la ligne.
 * 
 * @param n Le nombre à afficher.
 * @param fd Le descripteur de fichier de la sortie standard (généralement 1).
 */
void				ft_putlnbr_fd(long long n, int fd);

/**
 * @brief Affiche un nombre entier sur la sortie standard.
 * 
 * @param n Le nombre à afficher.
 * @param fd Le descripteur de fichier de la sortie standard (généralement 1).
 */
void				ft_putnbr_fd(int n, int fd);

/**
 * @brief Vérifie si un caractère est un chiffre.
 * 
 * @param i Le caractère à vérifier.
 * @return 1 si le caractère est un chiffre, 0 sinon.
 */
int					ft_isdigit(int i);

/**
 * @brief Convertit une chaîne de caractères en entier.
 * 
 * @param str La chaîne de caractères à convertir.
 * @return L'entier converti, ou 0 si la conversion échoue.
 */
int					ft_atoi(const char *str);

/**
 * @brief Analyse les arguments du programme et initialise les variables globales.
 * 
 * @param var Pointeur vers la structure contenant les variables globales.
 * @param ac Nombre d'arguments.
 * @param av Tableau d'arguments.
 * @return 0 si l'analyse se déroule correctement, -1 sinon.
 */
int					ft_arg(t_bin *var, int ac, char **av);

/**
 * @brief Crée les threads des philosophes.
 * 
 * @param var Pointeur vers la structure contenant les variables globales.
 * @return 0 si la création des threads se déroule correctement, -1 sinon.
 */
int					ft_create(t_bin *var);

/**
 * @brief Nettoie les ressources allouées pour les philosophes.
 * 
 * @param var Pointeur vers la structure contenant les variables globales.
 * @param i Indice du premier philosophe.
 * @param l Indice du dernier philosophe.
 * @return 0.
 */
int					ft_clear(t_bin *var, int i, int l);

/**
 * @brief Fonction exécutée par chaque thread de philosophe.
 * 
 * @param p_data Pointeur vers les données du philosophe.
 * @return NULL.
 */
void				*fn_philo(void *p_data);

/**
 * @brief Fonction de surveillance de l'état de santé d'un philosophe.
 * 
 * @param p_data Pointeur vers les données du philosophe.
 * @return NULL.
 */
void				*fn_monitor_eat(void *p_data);

/**
 * @brief Fonction de surveillance de l'état de santé des philosophes.
 * 
 * @param p_data Pointeur vers les données du programme.
 * @return NULL.
 */
void				*fn_monitor(void *p_data);

/**
 * @brief Retourne le timestamp actuel en millisecondes.
 * 
 * @return Le timestamp actuel.
 */
long long			current_timestamp(void);

/**
 * @brief Affiche la valeur d'un semaphore.
 * 
 * @param sem_die Pointeur vers le semaphore.
 * @param val Pointeur vers la variable qui contiendra la valeur du semaphore.
 */
void				print_value(sem_t *sem_die, int *val);

/**
 * @brief Affiche un message formaté avec le timestamp et l'identifiant du philosophe.
 * 
 * @param a Le timestamp.
 * @param n Pointeur vers le philosophe.
 */
void				ft_putlnbr_str(long long a, t_node *n);

/**
 * @brief Affiche un message formaté avec l'identifiant du philosophe.
 * 
 * @param a L'identifiant du philosophe.
 * @param n Pointeur vers le philosophe.
 */
void				ft_putnbr_str(int a, t_node *n);

/**
 * @brief Affiche un message formaté pour un philosophe.
 * 
 * @param n Pointeur vers le philosophe.
 * @param str Le message à afficher.
 * @param tm Le timestamp.
 * @param j L'identifiant du philosophe.
 */
void				ft_message(t_node *n, char *str, long long tm,\
unsigned int j);

/**
 * @brief Vérifie les arguments du programme.
 * 
 * @param ac Nombre d'arguments.
 * @param av Tableau d'arguments.
 * @return 0 si les arguments sont valides, -1 sinon.
 */
int					ft_check_arg(int ac, char **av);

/**
 * @brief Vérifie si une chaîne de caractères ne contient que des chiffres.
 * 
 * @param str La chaîne de caractères à vérifier.
 * @return 1 si la chaîne ne contient que des chiffres, 0 sinon.
 */
int					ft_strisdigit(char *str);

/**
 * @brief Affiche un message d'erreur formaté pour un philosophe et termine le programme.
 * 
 * @param n Pointeur vers le philosophe.
 * @param str Le message d'erreur à afficher.
 * @param tm Le timestamp.
 * @param j L'identifiant du philosophe.
 */
void				ft_message_die(t_node *n, char *str, long long tm,\
unsigned int j);

/**
 * @brief Lance les threads des philosophes et de surveillance.
 * 
 * @param var Pointeur vers la structure contenant les variables globales.
 * @return 0 si le lancement des threads se déroule correctement, -1 sinon.
 */
int					ft_go_thread(t_bin *var);

#endif

/**
 * @file struct.c
 * @brief Gestion des structures et des mutex pour les philosophes.
 * 
 * Ce fichier contient les fonctions nécessaires pour créer, initialiser
 * et nettoyer les structures utilisées dans le programme, notamment
 * les philosophes et leurs mutex.
 */

#include "philo_one.h"

/**
 * @brief Libère la mémoire et détruit les mutex.
 * 
 * Cette fonction détruit les mutex associés à chaque philosophe et
 * libère la mémoire allouée à la structure `philo`. Elle détruit également
 * le mutex global `lock_std`.
 * 
 * @param var Pointeur vers la structure contenant les variables globales.
 * @param i Indice du premier philosophe.
 * @param l Indice du dernier philosophe (0 si c'est le dernier, sinon 1).
 * @return Toujours retourne 1 (indique que l'opération a été effectuée).
 */
int ft_clear(t_bin *var, int i, int l)
{
    int j;

    j = 1;
    while (j < i + 1)
    {
        pthread_mutex_destroy(&(var->philo[i].lock)); /**< Destruction du mutex de verrouillage. */
        if (l == 0 && j == i)
            break;
        pthread_mutex_destroy(&(var->philo[i].eat)); /**< Destruction du mutex de temps de repas. */
        j++;
    }
    pthread_mutex_destroy(&(var->lock_std)); /**< Destruction du mutex global. */
    free(var->philo); /**< Libération de la mémoire allouée aux philosophes. */
    return (1);
}

/**
 * @brief Crée et initialise les structures des philosophes.
 * 
 * Cette fonction configure les structures de chaque philosophe, lie les mutex,
 * et initialise leurs valeurs par défaut. Chaque philosophe est relié
 * à un suivant pour former une liste circulaire.
 * 
 * @param var Pointeur vers la structure contenant les variables globales.
 * @param i Indice du premier philosophe.
 * @return Retourne 0 si la création est réussie, sinon une valeur différente de 0.
 */
static int ft_create_philo(t_bin *var, int i)
{
    while (i < var->nb + 1)
    {
        if (i == var->nb)
            var->philo[i].next = &(var->philo[1]); /**< Liaison au premier philosophe (liste circulaire). */
        else
            var->philo[i].next = &(var->philo[i + 1]); /**< Liaison au philosophe suivant. */

        var->philo[i].value = i; /**< Affectation de l'identifiant du philosophe. */
        var->philo[i].tt_die = var->time_to_die; /**< Temps avant de mourir sans manger. */
        var->philo[i].tt_eat = var->time_to_eat; /**< Temps nécessaire pour manger. */
        var->philo[i].tt_sleep = var->time_to_sleep; /**< Temps nécessaire pour dormir. */
        var->philo[i].count_eat = 0; /**< Compteur initialisé à 0. */
        var->philo[i].end = 0; /**< Indicateur de fin initialisé à 0. */
        var->philo[i].nb_eat = var->nb_eat; /**< Nombre de repas nécessaires. */
        var->philo[i].str[0] = '\0'; /**< Chaîne initialisée à vide. */
        var->philo[i].var = var; /**< Pointeur vers la structure globale. */
        var->philo[i].lock_std = &(var->lock_std); /**< Pointeur vers le mutex global. */

        if (pthread_mutex_init(&(var->philo[i].lock), NULL) != 0) /**< Initialisation du mutex de verrouillage. */
            return ((!(ft_clear(var, i, 0))));
        if (pthread_mutex_init(&(var->philo[i].eat), NULL) != 0) /**< Initialisation du mutex de repas. */
            return ((!(ft_clear(var, i, 1))));
        i++;
    }
    return (0);
}

/**
 * @brief Crée et initialise les structures principales du programme.
 * 
 * Cette fonction alloue la mémoire nécessaire pour les philosophes et
 * initialise les mutex globaux ainsi que les structures individuelles.
 * 
 * @param var Pointeur vers la structure contenant les variables globales.
 * @return Retourne 0 si la création est réussie, sinon 1.
 */
int ft_create(t_bin *var)
{
    if (pthread_mutex_init(&(var->lock_std), NULL) != 0) /**< Initialisation du mutex global. */
        return (1);
    if (!(var->philo = malloc((var->nb + 1) * sizeof(t_node)))) /**< Allocation mémoire pour les philosophes. */
    {
        pthread_mutex_destroy(&(var->lock_std)); /**< Destruction du mutex global en cas d'échec. */
        return (1);
    }
    if (ft_create_philo(var, 1)) /**< Appel de la fonction pour initialiser les philosophes. */
        return (1);
    return (0);
}
