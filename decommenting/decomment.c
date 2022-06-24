#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <stdlib.h>

enum StateType
{
    IN_NORMAL_CODE,
    IN_BLOCK_COMMENT,
    IN_CHAR_LITERAL,
    IN_STRING_LITERAL
};

int main(int argc, char const *argv[])
{
    int ch;
    enum StateType state = IN_NORMAL_CODE;
    bool AllClosed = true;

    int lineCtr = 1;
    int commentOpenedLine = NULL;
    enum StateType setStateType();
    enum StateType handleInStringLiteralState();
    enum StateType handleInCharLiteralState();
    enum StateType handleInBlockCommentState();
    enum StateType handleInNormalCodeState();

    int prev = NULL;

    while ((ch = getchar()) != EOF)
    {
        if (ch == '\n')
        {
            lineCtr += 1;
        }
        switch (state)
        {
        case IN_NORMAL_CODE:

            state = handleInNormalCodeState(ch, prev);
            if (state == IN_BLOCK_COMMENT)
            {
                AllClosed = false;
                commentOpenedLine = lineCtr;
            }
            prev = ch;
            break;

        case IN_BLOCK_COMMENT:
            state = handleInBlockCommentState(ch, prev);
            if (state == IN_NORMAL_CODE)
            {
                AllClosed = true;
                prev = NULL;
            }
            else
            {
                prev = ch;
            }
            break;
        case IN_CHAR_LITERAL:

            state = handleInCharLiteralState(ch);
            prev = ch;
            break;
        case IN_STRING_LITERAL:

            state = handleInStringLiteralState(ch);
            prev = ch;
            break;
        };
    }

    handleExitStatus(AllClosed, commentOpenedLine);
}

enum StateType handleInNormalCodeState(int ch, int prev)
{
    if (ch == '"')
    {
        display(ch);
        return IN_STRING_LITERAL;
    }
    else if (ch == '\'')
    {
        display(ch);
        return IN_CHAR_LITERAL;
    }
    else if (ch == '*' && prev == '/')
    {
        int space = ' ';
        display(space);
        return IN_BLOCK_COMMENT;
    }
    else if (prev == '/' && ch != '/')
    {
        display(prev);
        display(ch);
        return IN_NORMAL_CODE;
    }
    else if (prev == '/' && ch == '/')
    {
        display(prev);
        return IN_NORMAL_CODE;
    }
    else if (ch != '/')
    {
        display(ch);
        return IN_NORMAL_CODE;
    };
}

enum StateType handleInBlockCommentState(int ch, int prev)
{
    if (ch == '/' && prev == '*')
    {
        return IN_NORMAL_CODE;
    }
    else if (ch == '\n')
    {
        display(ch);
        return IN_BLOCK_COMMENT;
    }
    else
    {
        return IN_BLOCK_COMMENT;
    }
}

enum StateType handleInCharLiteralState(int ch)
{
    if (ch == '\'')
    {
        display(ch);
        return IN_NORMAL_CODE;
    }
    else
    {
        display(ch);
        return IN_CHAR_LITERAL;
    }
}

enum StateType handleInStringLiteralState(int ch)
{
    if (ch == '"')
    {
        display(ch);
        return IN_NORMAL_CODE;
    }
    else
    {
        display(ch);
        return IN_STRING_LITERAL;
    }
}

void handleExitStatus(bool exitStatus, int commentOpenedLine)
{
    if (exitStatus == false)
    {
        fprintf(stderr, "Error: line %d: unterminated comment\n", commentOpenedLine);
        exit(EXIT_FAILURE);
    }
    else if (exitStatus == true)
    {
        exit(EXIT_SUCCESS);
    }
}

void display(int c)
{
    putchar(c);
};

enum StateType setStateType(enum StateType state)
{
    return state;
}