    /* start */                                                        
    /* This whole section could probably be rewritten - it seems       
       like a bit of a mess right now */                               
    if (strncmp(sysInfo.sysname, "Linux", 5) == 0) {                   
        char *osContents = malloc(512);                                
        char *newContents = malloc(512);                               
        int line = 0;                                                  
        FILE *f = fopen("/etc/os-release", "rt");                      
        if (f == NULL || osContents == NULL)                           
            return "Linux";                                            
        /* look through each line of /etc/os-release until we're on the
         * NAME= line */                                               
        while (fgets(osContents, 512, f)) {                            
            snprintf(newContents, 512, "%.*s", 511, osContents + 4);   
            if (strncmp(newContents, "=", 1) == 0)                     
                break;                                                 
            line++;                                                    
        }                                                              
        fclose(f);                                                     
        free(osContents);                                              
        if (strncmp(newContents, "=", 1) == 0) {                       
            int len = strlen(newContents);                             
            for (int i = 0; i < len; i++) {                            
                if (newContents[i] == '\"' ||                          
                    newContents[i] == '=') {                           
                    for (int ii = 0; ii < len; ii++)                   
                        newContents[ii] =                              
                            newContents[ii + 1];                       
                    newContents[strlen(newContents) - 1] =             
                        '\0';                                          
                }                                                      
            }                                                          
        }                                                              
        if (osname == NULL)                                            
            osname = malloc(512);                                      
        strcpy(osname, newContents);                                   
        free(newContents);                                             
        /* end */
