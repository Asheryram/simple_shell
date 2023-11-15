#include "shell.h"

/**
 * process_exe_cute_core - this is the cor e execution function
 * @arginv: arg inventory
 *
 * Return: 0
 */
pid_t process_exe_cute_core(arg_in_ven_tory_t *arginv)
{
	unsigned int i;
	ptree_t *ptree;

	for (i = 0; i < arginv->pipeline.processesN; i++)
	{
		ptree = arginv->pipeline.processes[i].ptree;
		arginv->commands = ptree->strings;
		ptree->stringsN += expand_alias(arginv);
		ptree->strings = arginv->commands;
		arginv->pipeline.processes[i].pid = exe_cute(arginv);
	}
	return (arginv->pipeline.processes[arginv->pipeline.processesN - 1].pid);
}

/**
 * process_exe_cute_tree - this exe_cutes ptree
 * @arginv: arg inventory
 * @ptree: the parsing tree
 * @depth: the depth of parsing tree
 *
 * Return: the last pid
 */
pid_t process_exe_cute_tree(arg_in_ven_tory_t *arginv, ptree_t *ptree,
						  unsigned int depth)
{
	int status = 0, id, exe_cute = 1;
	pid_t last_pid = -1;

	if (!ptree)
		return (last_pid);
	id = ptree->token_id;
	if (id == TO_KEN_STRING || id == TO_KEN_PIPE || re_di_rec_tion(id))
	{ /* exe_cute pipeline */
		init_pipeline(&arginv->pipeline, ptree);
		last_pid = process_exe_cute_core(arginv);
		delete_pipeline(&arginv->pipeline);
		return (last_pid);
	} /* recursive call on each child */
	if (ptree->left)
	{
		last_pid = process_exe_cute_tree(arginv, ptree->left, depth + 1);
		if (id != TO_KEN_BACK_GROUND)
		{ /* wait for the child */
			waitpid(last_pid, &status, 0);
			status = WEXITSTATUS(status);
		}
		else
			arginv->n_bg_jobs++, arginv->last_bg_pid = last_pid;
		switch (status)
		{
		case 1:
			arginv->exit_status = 127;
			break;
		default:
			arginv->exit_status = status;
			break;
		}
		if ((id == TO_KEN_AND && status) || (id == TO_KEN_OR && !status))
			exe_cute = 0;
		if (exe_cute)
			last_pid = process_exe_cute_tree(arginv, ptree->right, depth + 1);
	}
	return (last_pid);
}

/**
 * process_exe_cute - exe_cutes background process
 * @arginv: arginv
 *
 * Return: 0 or exit
 */
int process_exe_cute(arg_in_ven_tory_t *arginv)
{
	pid_t last_pid;
	int status = 0;

	arginv->n_bg_jobs = 0;

	last_pid = process_exe_cute_tree(arginv, arginv->parser.tree, 0);

	if (last_pid != -1)
	{
		if (arginv->parser.tree->token_id != TO_KEN_BACK_GROUND)
		{
			waitpid(last_pid, &status, 0);
			status = WEXITSTATUS(status);
		}
		else
		{
			arginv->n_bg_jobs++;
			arginv->last_bg_pid = last_pid;
		}
		switch (status)
		{
		case 1:
			arginv->exit_status = 127;
			break;
		default:
			arginv->exit_status = status;
			break;
		}
	}
	return (0);
}
