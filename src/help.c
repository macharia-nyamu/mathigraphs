#include "../headers/mathigraphs.h"

void bar_help() 
{
    printf("\n=== Mathi Graphs: Bar Command Help ===\n\n");

    printf("Usage:\n");
    printf("  bar [options]\n\n");
    printf("Description:\n");
    printf("  Generate a bar graph from a CSV file with optional aggregation.\n\n");

    printf("Required options:\n");
    printf("  file='path/to/file.csv'   Specify the CSV file path\n");
    printf("  x='column_name'           Column to use for X-axis labels\n");
    printf("  y='column_name'           Column to use for Y-axis values\n\n");

    printf("Optional options:\n");
    printf("  title='Graph Title'       Title for the bar graph\n");
    printf("  compute='method'          Aggregation method for Y values per X label\n");
    printf("                            Available methods: avg (default), sum, max, min\n\n");

    printf("Behavior:\n");
    printf("  - If 'compute' is not specified, the average (avg) will be used.\n");
    printf("  - The bar length is scaled to fit the console width.\n");
    printf("  - Non-numeric Y values or missing labels will be skipped with a warning.\n\n");

    printf("Example:\n");
    printf("  bar file='assets/company.csv' x='Year' y='Salary' title='Average Salary per Year'\n");
    printf("  bar file='assets/company.csv' x='Year' y='Salary' compute='sum' title='Total Salaries per Year'\n\n");

    printf("Notes:\n");
    printf("  - Column names are case-insensitive.\n");
    printf("  - Ensure the CSV file exists and has a proper header row.\n");
    printf("  - Invalid 'compute' methods will be rejected with an error message.\n\n");
}