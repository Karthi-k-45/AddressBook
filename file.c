#include <stdio.h>
#include<string.h>
#include "file.h"

void saveContactsToFile(AddressBook *addressBook) {
  for (int j = 0; j < addressBook->contactCount - 1; j++) 
    {
        Contact temp;
        for (int k = 0; k < addressBook->contactCount - 1 - j; k++) 
        {
            if (strcmp(addressBook->contacts[k].name, addressBook->contacts[k + 1].name) > 0) 
            {
                temp = addressBook->contacts[k];
                addressBook->contacts[k] = addressBook->contacts[k + 1];
                addressBook->contacts[k + 1] = temp;
            }
        }
    }

  FILE *ptr;
  ptr=fopen("contact.csv","w");
  if(ptr==NULL)
  printf("file not exist");
else{
    fprintf(ptr,"#%d\n",addressBook->contactCount);
    for(int i=0;i<addressBook->contactCount;i++)
    {
        fprintf(ptr,"%s,%s,%s\n",addressBook->contacts[i].name
        ,addressBook->contacts[i].phone,
        addressBook->contacts[i].email);
    }
    
    
}
fclose(ptr);
printf("\nContacts saved sucessfully\n");
}

void loadContactsFromFile(AddressBook *addressBook) {
  FILE* ptr;
  ptr=fopen("contact.csv","r");
  if(ptr==NULL)
  {
    printf("invalid file");
    return;
  }
  fscanf(ptr,"#%d",&addressBook->contactCount);
  for(int i=0;i<addressBook->contactCount;i++)
  {
    fscanf(ptr,"\n%49[^,],%49[^,],%49[^\n]",addressBook->contacts[i].name
        ,addressBook->contacts[i].phone,
        addressBook->contacts[i].email);
  }
  printf("contacts loaded successfully");
    
}