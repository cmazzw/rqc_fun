int match(char *ptext,char *name)
{
   if(*name=='\0')
   {
      return(1);
   }
   if(*ptext=='\0')
   {
       if(*name=='*'&&*(name+1)=='\0')
         {
            return(1);
         }
       return(0);
   }
   if(*name!='*'&&*name!='?')
   {
       if(*name==*ptext)
          return  match(ptext+1,name+1);
       return(0);
   }
   if(*name=='*')
      return match(ptext+1,name)||match(ptext,name+1);
   return match(ptext+1,name+1);
}
