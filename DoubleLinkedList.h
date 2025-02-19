// Mohamed Abdelfatah Linked list
#include <iostream>

using namespace std;

template <class T>
class clsDbLinkedList 
{

protected :

    short _size = 0;

    void InsertAtMid (Node * &  PrevNode, T value)
    { // This function does not handle insertion at the beginning or end.
        Node * NewNode = new Node();

        NewNode->Value = value;
        NewNode->Prev = PrevNode;
        NewNode->Next = PrevNode->Next;
        PrevNode->Next = NewNode;
        if (NewNode->Next != NULL)
            NewNode->Next->Prev = NewNode; 
        _size++;
    }

    void DeleteAtMid (Node * &ToDelete)
    {// This function does not handle deleting at the beginning or end. 
        if (ToDelete == NULL || ToDelete->Prev == NULL || ToDelete->Next == NULL)
            return;

        ToDelete->Prev->Next = ToDelete->Next;
        ToDelete->Next->Prev = ToDelete->Prev;
        delete ToDelete;
        _size--;
    }
 
public :

    class Node 
    {

    public :

        T Value;
        Node * Prev;
        Node * Next;

        Node ()
        {
            Prev = NULL;
            Next = NULL;
        }

        
    };

    Node * Head = NULL;
    Node * End = NULL;

    clsDbLinkedList ()
    {
        Head = NULL;
        End = NULL;
    }   

    ~clsDBLinkedList ()
    {
        Clear();
    }

    void Print ()
    {
        if (Head == NULL)
            return;
            
        Node * Current = Head;
        while (Current != NULL)
        {
            cout << Current->Value << "  ";
            Current = Current->Next;
        }

        cout << "\n";
    }

    void InsertAtTheBegining (T value)
    {
        Node * FirstNode = new Node();

        FirstNode->Prev = NULL;
        FirstNode->Value = value;
        FirstNode->Next = Head;

        if (Head != NULL) // if the List is not empty
            Head->Prev = FirstNode;

        else  // if it only one node in the linked list
            End = FirstNode;
    
        Head = FirstNode;
        _size++;

    }

    void InsertAtTheEnd (T value)
    {
        
        if (Head == NULL || End == NULL)
        {
            InsertAtTheBegining(value);
            return;
        }

        Node * NewLast = new Node();

        NewLast->Value = value;
        NewLast->Next = NULL;

        End->Next = NewLast;

        NewLast->Prev = End;
        End = NewLast;
        _size++;
    }

    void InsertAfter (int Index, T value)
    {
        if (Index >= _size || Index < 0) // if index is not exist it won't enter
            return;

        if (Index == 0)
        {
            InsertAtTheBegining(value);
            return;
        }

        if (Index == _size-1)
        {
            InsertAtTheEnd(value);
            return;
        }

        Node * Current = GetNode(Index);
        InsertAtMid(Current, value);
    }


    void DeleteFirstNode ()
    {
        if (Head == NULL)
            return;

        Node * FirstToDelete = Head;

        if (Head->Next == NULL) // if list has only one node that will delete
        {
            Head = NULL;
            End = NULL;
        }    
        else // if node has more than one node
        {
            Head = Head->Next;
            Head->Prev = NULL;  
        }
        
        delete FirstToDelete;
        _size--;
    }

    void DeleteLastNode ()
    {
        if (Head == NULL || End == NULL)
            return;

        if (Head->Next == NULL) // if First node is the last
        {
            delete Head;
            Head = NULL;
            End = NULL;
            _size--; 
            return;
        }

        Node * Current = End;
        End = Current->Prev;
        End->Next = NULL;
        delete Current;
        _size--; 
    }

    void DeleteNode (int Index)
    {
        if (Head == NULL || Index < 0 || Index >= _size)
            return;

        // If deleting the first node
        if (Index == 0)
        {
            DeleteFirstNode();
            return;
        }

        // If deleting the last node
        if (Index == _size-1)
        {
            DeleteLastNode();
            return;
        }

        // General case: deleting a middle node
        Node * Current = GetNode(Index);
        DeleteAtMid(Current);
        
    }

    short Size ()
    {
        return _size;
    }

    bool IsEmpty ()
    {
        return _size == 0;
    }

    void Clear ()
    {
        Node * Current = Head;
        Node * Next;
        while (Current != NULL)
        {
            Next = Current->Next;
            delete Current;
            Current = Next;
        }
        Head = NULL;
        End = NULL;
        _size = 0;
    }

    void Inverse ()
    {
        if (_size == 0 || _size == 1)
            return;

        Node * Current = Head;
        Node * Temp = NULL;

        while (Current != NULL)
        {
            Temp = Current->Prev;
            Current->Prev = Current->Next;
            Current->Next = Temp;
            Current = Current->Prev;
        }

        End = Head;

        if (Temp != NULL) // cuz if it one node and temp is null
            Head = Temp->Prev; 
    /*  Head equal Temp->Prev cuz each time when current updated to become the prev the temp still at the prev 
        of the last iteration till it updated in the begining of the next iteration ,so when current become NULL
        temp doesn't updated cuz loop doessn't entered so temp still at the second last node not at last   
        why Head = Temp->Prev not Temp->Next cuz temp is just a pointer points to an object that is prev and next has been updated*/
        

    }

    T GetItem (int index)
    {
        Node * Item = GetNode(index);
        if (Item == NULL)
            return 0;

        return Item->Value;
    }

    bool UpdateItem (int index, T new_value)
    {
        Node * item = GetNode(index);
        if (item != NULL)
        {
            item->Value = new_value;
            return true;
        }
        else
            return false;
    }

    Node * GetNode (int index)
    {

        if (index >= _size || index < 0)  // if index == size - 1 return End
            return NULL;

        int counter = 0;

        Node *Current = Head;

        while (Current != NULL && Current->Next != NULL) // to check from the index existence
        {
            if (counter == index)
                break;

            Current = Current->Next;
            counter++;
        }

        return Current;
    }
    
    Node* Find (T value)
    {
        Node * Current = Head;

        while (Current != NULL)
        {
            if (Current->Value == value)
                return Current;

            Current = Current->Next;
        }

        return NULL;
    }


};