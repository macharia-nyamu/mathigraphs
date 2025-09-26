#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../headers/mathigraphs.h"

#define MAX_BAR_WIDTH 50

// Helper: trim whitespace
static void trim(char *s) {
    char *end;
    while (*s == ' ' || *s == '\t') s++;  // leading
    if (*s == 0) return;
    end = s + strlen(s) - 1;
    while (end > s && (*end == ' ' || *end == '\n' || *end == '\r')) *end-- = '\0';
}

// Helper: repeat character
static void repeat_char(char c, int count) {
    for (int i = 0; i < count; i++) putchar(c);
}

// Get option value from command
char* get_option_value(const char *command, const char *key) 
{
    char *pos = strstr(command, key);
    if (!pos) return NULL;

    pos += strlen(key); // next should be '
    if (*pos != '\'') return NULL; // next not '
    pos++; // ahead of '

    char *end = strchr(pos, '\''); // start from ahead '
    if (!end) return NULL;

    size_t len = end - pos;
    char *value = malloc(len + 1);
    if (!value) return NULL;
    strncpy(value, pos, len);
    value[len] = '\0';
    return value;
}

// Draw bar graph
void draw_bar(const BarOptions *opts) 
{
    FILE *fp = fopen(opts->file, "r");
    if (!fp) 
    {
        printf("Error: could not open file: %s\n", opts->file);
        return;
    }

    char line[1024];
    if (!fgets(line, sizeof(line), fp)) 
    {
        printf("Error: empty file\n");
        fclose(fp);
        return;
    }

    // Find X and Y column indexes
    int colX_idx = -1, colY_idx = -1, idx = 0;
    char *token = strtok(line, ",");
    while (token) 
    {
        trim(token);
        char lower[128];
        strncpy(lower, token, sizeof(lower)); lower[sizeof(lower)-1]=0;
        mathi_string_to_lower(lower);

        if (strcmp(lower, opts->x) == 0) colX_idx = idx;
        if (strcmp(lower, opts->y) == 0) colY_idx = idx;

        idx++;
        token = strtok(NULL, ",");
    }

    if (colX_idx == -1 || colY_idx == -1) 
    {
        printf("Error: columns not found in header\n");
        fclose(fp);
        return;
    }

    // Read data and aggregate
    Group groups[500];
    int gcount = 0;

    while (fgets(line, sizeof(line), fp)) 
    {
        idx = 0;
        token = strtok(line, ",");
        char *xval = NULL, *yval = NULL;

        while (token) 
        {
            trim(token);
            if (idx == colX_idx) xval = token;
            if (idx == colY_idx) yval = token;
            idx++;
            token = strtok(NULL, ",");
        }

        if (!xval || !yval) continue;

        char *endptr;
        double val = strtod(yval, &endptr);
        if (endptr == yval || *endptr != '\0') continue;

        int found = 0;
        for (int i = 0; i < gcount; i++) 
        {
            if (strcmp(groups[i].label, xval) == 0) 
            {
                groups[i].sum += val;
                groups[i].count++;
                if (val < groups[i].min) groups[i].min = val;
                if (val > groups[i].max) groups[i].max = val;
                found = 1;
                break;
            }
        }

        if (!found) 
        {
            groups[gcount].label = strdup(xval);
            groups[gcount].sum = val;
            groups[gcount].count = 1;
            groups[gcount].min = val;
            groups[gcount].max = val;
            gcount++;
        }
    }
    fclose(fp);

    if (gcount == 0) { printf("No rows to plot.\n"); return; }

    // Compute values
    double values[500], maxVal = -1e9;
    int useSum=0, useAvg=0, useMax=0, useMin=0;
    if (!opts->compute) useAvg = 1;
    else 
    {
        if (strcmp(opts->compute,"sum")==0) useSum=1;
        else if (strcmp(opts->compute,"avg")==0) useAvg=1;
        else if (strcmp(opts->compute,"max")==0) useMax=1;
        else if (strcmp(opts->compute,"min")==0) useMin=1;
        else { printf("Error: unknown compute '%s'.\n", opts->compute); return; }
    }

    for (int i=0;i<gcount;i++)
    {
        if (useSum) values[i]=groups[i].sum;
        else if (useAvg) values[i]=groups[i].sum/groups[i].count;
        else if (useMax) values[i]=groups[i].max;
        else if (useMin) values[i]=groups[i].min;
        if (values[i]>maxVal) maxVal=values[i];
    }

    // the optional sort
    if (opts->sort) 
    {
        if (strcmp(opts->sort,"y")==0)
        {
            // sort by value descending
            for(int i=0;i<gcount-1;i++)
                for(int j=i+1;j<gcount;j++)
                    if(values[j]>values[i])
                    {
                        double tmp=values[i]; values[i]=values[j]; values[j]=tmp;
                        char *tlabel=groups[i].label; groups[i].label=groups[j].label; groups[j].label=tlabel;
                    }
        } 
        else if (strcmp(opts->sort,"x")==0)
        {
            // sort by label alphabetically
            for(int i=0;i<gcount-1;i++)
                for(int j=i+1;j<gcount;j++)
                    if(strcmp(groups[i].label,groups[j].label)>0)
                    {
                        double tmp=values[i]; values[i]=values[j]; values[j]=tmp;
                        char *tlabel=groups[i].label; groups[i].label=groups[j].label; groups[j].label=tlabel;
                    }
        } 
        else 
        {
            printf("Warning: unknown sort option '%s'. Ignored.\n", opts->sort);
        }
    }

    // Print title
    if (opts->title) printf("\n%s\n\n", opts->title);

    // Draw bars
    for(int i=0;i<gcount;i++)
    {
        int barLen=(int)((values[i]/maxVal)*MAX_BAR_WIDTH);
        printf("%-15s | ", groups[i].label);
        repeat_char('#', barLen);
        printf(" (%.2f)\n", values[i]);
        free(groups[i].label);
    }
    printf("\n");
}

// Display bar command
void display_bar(char *command)
{
    BarOptions opts={0}; // null all members
    opts.file=get_option_value(command,"file=");
    opts.x=get_option_value(command,"x=");
    opts.y=get_option_value(command,"y=");
    opts.title=get_option_value(command,"title=");
    opts.compute=get_option_value(command,"compute=");
    opts.sort=get_option_value(command,"sort=");

    // lowercase strings // from mathi c
    if(opts.x) mathi_string_to_lower(opts.x);
    if(opts.y) mathi_string_to_lower(opts.y);
    if(opts.compute) mathi_string_to_lower(opts.compute);
    if(opts.sort) mathi_string_to_lower(opts.sort);

    // Validate required
    if(!opts.file || !opts.x || !opts.y)
    {
        printf("Missing required options: file, x, y\n");
        goto cleanup;
    }

    if(!mathi_file_exists(opts.file))
    {
        printf("Error: file not found -> %s\n", opts.file);
        goto cleanup;
    }

    long fsize=mathi_file_size(opts.file);
    if(fsize<=0)
    {
        printf("Error: file empty or unreadable -> %s\n", opts.file);
        goto cleanup;
    }

    // Check header
    FILE *fp=mathi_filex_open(opts.file,"r");
    if(!fp)
    { 
        printf("Error opening file.\n"); goto cleanup; 
    }
    char line[1024];
    if(!mathi_file_read_line(fp,line,sizeof(line)))
    {
        printf("Error: cannot read CSV header\n"); mathi_filex_close(fp); goto cleanup;
    }
    mathi_filex_close(fp);

    int foundX=0,foundY=0;
    char *token=strtok(line,",");
    while(token)
    {
        while(*token==' ') token++;
        char *end=token+strlen(token)-1;
        while(end>token && (*end==' '||*end=='\n')) *end='\0', end--;
        if(strcmp(token,opts.x)==0) foundX=1;
        if(strcmp(token,opts.y)==0) foundY=1;
        token=strtok(NULL,",");
    }
    if(!foundX || !foundY)
    {
        printf("Error: columns not found -> x:%s y:%s\n",opts.x,opts.y);
        goto cleanup;
    }

    draw_bar(&opts);

cleanup:
    if(opts.file) free(opts.file);
    if(opts.x) free(opts.x);
    if(opts.y) free(opts.y);
    if(opts.title) free(opts.title);
    if(opts.compute) free(opts.compute);
    if(opts.sort) free(opts.sort);
}
