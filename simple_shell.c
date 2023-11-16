int main(int ac, char **av)
{
 if (ac == 2)
  args.fd = open(av[1], O_RDONLY);

 if (args.fd == -1)
 {
  print_error(&args);
  exit(1);
 }

  while (1)
 {
    /*if interactive print the prompt (eg. myshell->)*/

    if (interactive(ac))
       write(STDOUT_FILENO, args.prompt, _strlen(args.prompt));

  read_chars = _getline(&args.line, &size, args.fd);

  /*EOF: enf of file or Ctrl + D*/
  if (read_chars == -1)
  {
   free(args.line);
   exit(0);
  }

  /* case of Empty line*/
  if (read_chars == 1 && args.line[0] == '\n')
  {
   free(args.line);
   continue;
  }

  /* normal cases */

  args.line[read_chars - 1] = '\0';
  remove_comments(&args);
  make_commands(&args.commands, args.line);
  variable_replacement(&args);
  execute(&args);
 }
