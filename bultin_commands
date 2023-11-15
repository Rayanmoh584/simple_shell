while (getcmd (buf, sizeof(buf))>=0){
    if (buf[0] == 'c' && buf[1] == 'd' && buf[2] == ''){
        buf[strlen(buf)-1] =0;
        if (chdir(buf+3)<0)
        fprintf(2, "cannot cd %s\n", buf+3);
    continue
    }
    if (fork1() == 0)
    runcmd(parsecmd(buf));
wait(0);
}
exit(0);
}