int reglen(char *s)
{
    int num=0;
    int i = 0;      
    while(s[i]!='\0')
      {
        if(s[i]>='a'&&s[i]<='z')
          num++;
        else if(s[i]>='A'&&s[i]<='Z')
          num++;
        else if(s[i]=='/' || s[i]=='-' || s[i]==' ' || s[i]=='=')
          num++;
        else if(s[i]>='0'&&s[i]<='9')
          num++;
        i++;
      }
    return num;
}
