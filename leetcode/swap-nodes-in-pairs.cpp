struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *swapPairs(ListNode *head) {
        if (head == nullptr || head->next == nullptr)
        {
            return head;
        }
        
        ListNode *c = head;
        ListNode *p = nullptr;
        ListNode *n = nullptr;
        head = head->next;

        while (c && c->next)
        {
            n = c->next;

            if (p != nullptr)
            {
                p->next = n;
            }

            c->next = n->next;
            n->next = c;
            p = c;
            c = c->next;
        }

        return head;
    }
};