#include <stdio.h>

#define INFINITY 99999

void main()
{
    // Accept the no. of nodes
    int n;
    printf("\n\nEnter the no. of nodes: ");
    scanf("%d", &n);
    
    // Create a struct router with distance and adjacent array
    struct router
    {
        int distance[n];
        int adjacent[n];
    } node[n];
    
    int i, j, k, value;
    
    // Accept distance between all nodes to each other
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            // Distance of the node to itself is 0, else accept distance
            if(i == j)
                node[i].distance[j] = 0;
            else if(j < i)
                continue;
            else
            {
                // Accept and store the distance between nodes in the distance array of the first node
                printf("\n[Enter -1 if no path exists]\nEnter the distance from Router[%d] to Router[%d]: ", (i+1), (j+1));
                scanf("%d", &value);
                
                // Assign first node's adjacent node index with the index of second node, if path exists
                if(value == -1)
                {
                    node[i].distance[j] = INFINITY;
                    node[j].distance[i] = INFINITY;
                }
                else
                {
                    node[i].distance[j] = value;
                    node[j].distance[i] = value;
                    
                    node[i].adjacent[j] = j;
                    node[j].adjacent[i] = j;
                }
            }
        }
    }
    
    for(i = 0; i < n; i++)
    {
        for(j = 0; j < n; j++)
        {
            for(k = 0; k < n; k++)
            {
                // Assign the shortest distance from one node to another, whether it is a direct path or via another node
                if(node[i].distance[j] > node[i].distance[k] + node[k].distance[j])
                {
                    node[i].distance[j] = node[i].distance[k] + node[k].distance[j];
                    node[j].distance[i] = node[i].distance[j];
                    
                    // Reassign first node's adjacent node index with the index of intermediate node
                    node[i].adjacent[j] = k;
                    node[j].adjacent[i] = k;
                }
            }
        }
    }
    
    for(i = 0; i < n; i++)
    {
        // Print the Router Distance Table for each node
        printf("\n\nRouter[%d] Distance Table:\n", (i + 1));
        for(j = 0; j < n; j++)
        {
            if(i == j)
                printf("\nDistance to Router[%d] => 0", (j + 1));
            else if(node[i].distance[j] == INFINITY)
                printf("\nDistance to Router[%d] => No Path", (j + 1));
            else if((node[i].adjacent[j] + 1) == (j + 1))
                printf("\nDistance to Router[%d] => %d", (j + 1), node[i].distance[j]);
            else
                printf("\nDistance to Router[%d] via Router[%d] => %d", (j + 1), (node[i].adjacent[j] + 1), node[i].distance[j]);
        }
    }
    
    printf("\n\n");
}
