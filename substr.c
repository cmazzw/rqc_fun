int substr(char dst[], char src[],int start, int len)
{
    int i;
    for(i=0;i<len;i++)
    {
        dst[i]=src[start+i];    //从第start+i个元素开始向数组内赋值  
    }
    dst[i]='\0';
    return i;
}
