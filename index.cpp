/*
    Time Complexity = O(N * (W ^ 2))
    Space Complexity = O(N * W)

    Where N is the number of elements in the given array/list and W is the maximum length of a string.
*/

class TrieNode
{
public:

    //    Each Trie Node contains a HashMap 'children' where each alphabet points to a Trie Node.
    unordered_map<char, TrieNode *> children;

    //    'isEnd' is true if the node represents end of a contact.
    bool isEnd;

    //    Constructor
    TrieNode()
    {
        isEnd = false;
    }

    ~TrieNode()
    {
        for (unordered_map<char, TrieNode *>::iterator i = children.begin(); i != children.end(); i++)
        {
            delete i->second;
        }
    }
};

void insertContact(string &str, TrieNode *root)
{
    int n = str.length();

    //    'itr' is used to iterate the Trie Nodes
    TrieNode *itr = root;

    for (int i = 0; i < n; i++)
    {

        //    Check if the str[i] is already present in our Trie.
        TrieNode *next = itr->children[str[i]];

        if (next == NULL)
        {
            //   If not found then create a new TrieNode
            next = new TrieNode();

            //    Insert into the map.
            itr->children[str[i]] = next;
        }

        //    Move the iterator('itr') to point to next Trie Node.
        itr = next;

        //    If its the last character of the string 'str' then mark 'isEnd' as true
        if (i == n - 1)
        {
            itr->isEnd = true;
        }
    }
}

void viewSuggestionsHelper(TrieNode *curr, string prefix, vector<string> &temp)
{
    //    Check if the string 'prefix' ends at this Node If yes then display the string found so far
    if (curr->isEnd)
    {
        temp.push_back(prefix);
    }

    //    Find all the adjacent Nodes to the current Node and then call the function recursively.
    for (char c = 'a'; c <= 'z'; c++)
    {
        TrieNode *next = curr->children[c];

        if (next != NULL)
        {
            viewSuggestionsHelper(next, prefix + (char)c, temp);
        }
    }
}

vector<vector<string>> viewSuggestions(string &str, TrieNode *root)
{
    TrieNode *prev = root;

    string prefix = "";

    int n = str.length();

    vector<vector<string>> result;

    for (int i = 0; i < n; i++)
    {
        //    'prefix' stores the string formed so far.
        prefix.append(1, (char)str[i]);

        //    Get the last character entered.
        char lastCharacter = prefix[i];

        //    Find the Node corresponding to the last character of 'prefix' which is pointed by prev of the Trie.
        TrieNode *curr = prev->children[lastCharacter];

        //    If nothing found, then break the loop as no more prefixes are going to be present.
        if (curr == NULL)
        {
            i++;
            break;
        }

        //    If present in trie then insert all the contacts with given prefix in the result.
        vector<string> temp;

        viewSuggestionsHelper(curr, prefix, temp);

        result.push_back(temp);

        temp.clear();

        //    Change prev for next prefix
        prev = curr;
    }

    delete root;

    return result;
}

void insertContactList(vector<string> &contactList, TrieNode *root)
{

    int n = contactList.size();

    //    Insert each contact into the trie.
    for (int i = 0; i < n; i++)
    {
        insertContact(contactList[i], root);
    }
}

vector<vector<string>> phoneDirectory(vector<string> &contactList, string &queryStr)
{
    TrieNode *root = new TrieNode();

    //    Insert all the Contacts into Trie.
    insertContactList(contactList, root);

    //    Return the corresponding suggestions.
    return viewSuggestions(queryStr, root);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
