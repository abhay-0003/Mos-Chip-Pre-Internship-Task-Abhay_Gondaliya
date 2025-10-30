// Write a loop equivalent to the for loop above without using && or ||. 
//Original loop
for (i = 0; i < lim-1 && (c = getchar()) != '\n' && c != EOF; ++i)
    s[i] = c;

    
//Equivalent code(without && or ||)    
i = 0;
while (i < lim - 1) {
    c = getchar();

    if (c == EOF)
        break;
    if (c == '\n')
        break;

    s[i] = c;
    ++i;
}

