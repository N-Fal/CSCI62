#ifndef POST_H
#define POST_H

#include <string>


class Post
{
public:

    // pre: none
    // post: initializes a default Post object
    Post();

    // pre: none
    // post: initializes a Post object with the given values
    Post(int messageId, int ownerId, std::string message, int likes);

    // pre: none
    // post: returns "[message_] Liked by [likes_] people."
    virtual std::string toString();

    // pre: none
    // post: returns the messageId of this Post
    int getMessageId();

    // pre: none
    // post: returns a constant of the messageId of this Post
    int getMessageId() const;

    // pre: none
    // post: returns the ownerId of this Post 
    int getOwnerId();

    // pre: none
    // post: returns the message_ of this Post
    std::string getMessage();

    // pre: none
    // post: returns the number of likes this Post has
    int getLikes();
    
    // pre: none
    // post: returns ""
    virtual std::string getAuthor();

    // pre: none
    // post: returns true
    virtual bool getIsPublic();

private:
    int messageId_;
    int ownerId_;
    std::string message_;
    int likes_;

    // INVARIANTS:
    // messageId_ is the id of this message
    // ownerId_ is the id of the writer of this message
    // message_ is the content of this post
    // likes_ is the number of likes this post has
};

class IncomingPost : public Post
{
public:

    // pre: none
    // post: initializes a default IncomingPost object
    IncomingPost();

    // pre: none
    // post: initializes an IncomingPost object with the given values
    IncomingPost(int messageId, int ownerId, std::string message, int likes, bool isPublic, std::string author);

    // pre: none
    // post: returns "[author_] wrote [private]: [toString]"
    std::string toString();

    // pre: none
    // post: reuturns the author_ of this IncomingPost
    std::string getAuthor();

    // pre: none
    // post: returns the value of isPublic_ of this IncomingPost
    bool getIsPublic();

private:
    std::string author_;
    bool isPublic_;

    // INVARIANTS:
    // author_ is the name of the author of this post
    // isPublic_ denotes whether this is a public or private post
};
#endif