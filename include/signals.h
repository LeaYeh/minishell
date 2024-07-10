/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldulling <ldulling@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/18 18:35:55 by lyeh              #+#    #+#             */
/*   Updated: 2024/06/01 11:50:09 by ldulling         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "defines.h"

void	handle_signal_std(int signo, siginfo_t *info, void *context);
void	handle_signal_record(int signo, siginfo_t *info, void *context);
void	setup_signal(int signo, t_sig state);
void	raise_error_and_escape(t_sh *shell, char *msg);
void	raise_error_to_all_subprocess(t_sh *shell, int exit_code, char *msg);
void	raise_error_to_own_subprocess(t_sh *shell, int exit_code, char *msg);

#endif
