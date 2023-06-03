#include <stddef.h>
#include "ll_cycle.h"

int ll_has_cycle(node *head) {
    /* your code here */
    node *fast = head;
    node *slow = head;
    while (fast != NULL) {
        fast = fast->next;
        slow = slow->next;
        if (fast == NULL) {
            return 0;
        }
        else {
            fast = fast->next;
        }
        if (fast == slow) {
            return 1;
        }
    }
    return 0;
}