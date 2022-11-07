#include <stdio.h>  // to use standard input-output library
#include <stdlib.h> //to create structures
#include <string.h> // to use string functions
#include <math.h>   // to use random function for priorities of nodes

struct treapnode
{
  // creating structure of node.

  char word[128];
  char meaning[256];
  struct treapnode *left, *right; // pointers to left & right subtree
  double priority;                // priority to maintain heap property
};

struct treapnode *root = NULL; // intialising root node to NULL.

struct treapnode *createNode(char *word, char *meaning, double p)
{
  // function to create a node with required values.

  struct treapnode *tempnode;
  tempnode = (struct treapnode *)malloc(sizeof(struct treapnode));
  strcpy(tempnode->word, word);
  strcpy(tempnode->meaning, meaning);
  tempnode->priority = p;
  tempnode->left = tempnode->right = NULL;
  return tempnode;
}

/*
     Debugging rotations for heap properties.

void leftrotate(struct treapnode *k1)
{
  struct treapnode *k2;
  k2 = k1->right;
  k1->right = k2->left;
  k2->left = k1;
  k1 = k2;
}

// ROTATE RIGHT
void rightrotate(struct treapnode *k1)
{
  struct treapnode *k2;
  k2 = k1->left;
  k1->left = k2->right;
  k2->right = k1;
  k1 = k2;
}
*/

void leftrotate(struct treapnode *root)
{
  // left rotation of node.....

  struct treapnode *R = root->right;
  struct treapnode *X = root->right->left;
  R->left = root;
  root->right = X;
  root = R;
}
void rightrotate(struct treapnode *root)
{
  // right rotation of node........

  struct treapnode *L = root->left;
  struct treapnode *Y = root->left->right;
  L->right = root;
  root->left = Y;
  root = L;
}

void insert(char *word, char *meaning, double priority)

// function to insert node into tree with required constraints.

{
  struct treapnode *parent = NULL, *current = NULL, *tempnode = NULL;
  int temp2 = 0;
  if (!root)
  {
    root = createNode(word, meaning, priority);
    return;
  }
  for (current = root; current != NULL;
       current = (temp2 > 0) ? current->right : current->left)
  {
    temp2 = strcasecmp(word, current->word);
    if (temp2 == 0)
    {
      printf("Word Already Exists!!\n");
      return;
    }
    parent = current;
  }
  tempnode = createNode(word, meaning, priority);
  if (temp2 > 0)
  {
    // inserting tempnode to right of parent...
    parent->right = tempnode;
    if (tempnode->right != NULL && tempnode->priority > parent->priority)
    {
      // if parent node has less priority then child we will do rotations.
      leftrotate(tempnode);
    }
  }
  else
  {
    // inserting tempnode to left of parent...
    parent->left = tempnode;
    if (tempnode->left != NULL && tempnode->priority > parent->priority)
    {
      // if parent node has less priority then child we will do rotations.
      rightrotate(tempnode);
    }
  }
  return;
}

void deleteNode(char *str)
{
  // function to delete node...
  struct treapnode *parent = NULL, *current = NULL, *temp = NULL;
  int flag = 0, temp2 = 0;
  if (!root)
  {
    printf("Not present!!\n");
    return;
  }
  current = root;
  while (1)
  {
    temp2 = strcasecmp(current->word, str);
    if (temp2 == 0)
      break;
    flag = temp2;
    parent = current;
    current = (temp2 > 0) ? current->left : current->right;
    if (current == NULL)
      return;
  }
  //  deleting leaf node
  if (current->right == NULL)
  {
    if (current == root && current->left == NULL)
    {
      free(current);
      root = NULL;
      return;
    }
    else if (current == root)
    {
      root = current->left;
      free(current);
      return;
    }
    flag > 0 ? (parent->left = current->left) : (parent->right = current->left);
  }
  else
  {
    // delete node with single child
    temp = current->right;
    if (!temp->left)
    {
      temp->left = current->left;
      if (current == root)
      {
        root = temp;
        free(current);
        return;
      }
      flag > 0 ? (parent->left = temp) : (parent->right = temp);
    }
    else
    {
      // delete node with two children
      struct treapnode *successor = NULL;
      while (1)
      {
        successor = temp->left;
        if (!successor->left)
          break;
        temp = successor;
      }
      temp->left = successor->right;
      successor->left = current->left;
      successor->right = current->right;
      if (current == root)
      {
        root = successor;
        free(current);
        return;
      }
      (flag > 0) ? (parent->left = successor) : (parent->right = successor);
    }
  }
  free(current);
  return;
}

void search(char *str)
{
  // function to search any word.....

  struct treapnode *temp = NULL;
  int flag = 0, temp2 = 0;
  if (root == NULL)
  {
    printf("Dictionary is out of station!!\n");
    return;
  }
  temp = root;
  while (temp)
  {
    if ((temp2 = strcasecmp(temp->word, str)) == 0)
    {
      printf("Word : %s", str);
      printf("Meaning: %s", temp->meaning);
      flag = 1;
      break;
    }
    temp = (temp2 > 0) ? temp->left : temp->right;
  }
  if (!flag)
    printf("\nSearch Element not found in Dictionary\n");
  return;
}

void printdictionary(struct treapnode *node)
{
  if (root == NULL)
    printf("\nEmpty dictionary!!!");

  else if (node != NULL)
  {
    printdictionary(node->left);

    printf("\nWord: %s", node->word);
    printf("Meaning: %s", node->meaning);
    printf("Priority: %lf\n", node->priority);

    printdictionary(node->right);
  }
}

void update(char *str)
{
  struct treapnode *temp = NULL;
  int flag = 0, res = 0;

  if (root == NULL)
  {
    printf("Dictionary is out of station!!\n");
    return;
  }
  temp = root;
  while (temp)
  {
    if ((res = strcasecmp(temp->word, str)) == 0)
    {
      printf("Enter updated meaning: ");
      char mean[128];
      fgets(mean, 100, stdin);
      strcpy(temp->meaning, mean);
      flag = 1;
      break;
    }
    temp = (res > 0) ? temp->left : temp->right;
  }
  if (!flag)
    printf("Such element doesn't exist in our dictionary!!!\n");
  return;
}

int main()
{
  int ch;
  double priority;
  char str[128], meaning[256], mean[128];

  //      Just making intro here

  printf("\n\n**---------  Welcome to Our Dictionary  -------**\n");
  printf("Please choose below choice as per your desire to start execution\n\n");
  while (1)
  {
    printf("\n1. Insertion\t2. Deletion\n");
    printf("3. Searching\t4. View\n");
    printf("5. Update\t6. Exit\n\nEnter your choice: ");
    scanf("%d", &ch);
    getchar();
    switch (ch)
    {
    case 1:
      printf("\nEnter word: ");
      fgets(str, 100, stdin);
      printf("\nEnter Meaning: ");
      fgets(meaning, 256, stdin);
      priority = rand();
      insert(str, meaning, priority);
      break;
    case 2:
      printf("Enter the word to delete: ");
      fgets(str, 100, stdin);
      deleteNode(str);
      break;
    case 3:
      printf("Enter the search word: ");
      fgets(str, 100, stdin);
      search(str);
      break;
    case 4:
      printdictionary(root);
      break;
    case 5:
      printf("Enter the word to be updated: ");
      fgets(str, 100, stdin);

      update(str);
      break;

    case 6:
      printf("\n\n**---------  THANKS  -------**\n\n\n");
      exit(0);
    default:
      printf("You have entered wrong option!!!.. Please select again.\n");
      break;
    }
  }

  return 0;
}