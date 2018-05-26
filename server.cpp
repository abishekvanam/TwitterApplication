
struct user
{
	int uid;
	char *username;
	char *email;
	int followers;
	int following;
	int my_tweet_count;
};

struct tweet
{
	int tid;
	int uid;
	char *username;
	char *tweet_text;
};

struct comment
{
	int cid;
	int tid;
	int uid;
	char *username;
	char *comment_text;
};


char* get_password_from_file(char *);
int name_present_in_db(char *);
void signup_view();
int searchbyname(char *);
void store_in_db(char* username, char* password, char* email);


int storetweet(int uid,char *tweet)
{
	return createTweet(uid, tweet);
}

struct comment **getCommentServers(int tid, int *count)
{
	struct commentsfile** comments_from_db = getComments(tid, count);
	struct comment** tweet_comments = (struct comment**)malloc((*count)*sizeof(struct comment*));
	for (int i = *count - 1; i >= 0; i--)
	{
		struct comment* tweet_comment = (struct comment*)malloc(sizeof(struct comment));
		tweet_comment->cid = comments_from_db[i]->cid;
		tweet_comment->tid = comments_from_db[i]->tid;
		tweet_comment->uid = comments_from_db[i]->uid;
		struct userfile* user = getUserDetails(comments_from_db[i]->uid);
		tweet_comment->username = user->uname;
		tweet_comment->comment_text = comments_from_db[i]->comment;
		tweet_comments[i] = tweet_comment;
	}
	return tweet_comments;
}




struct tweet** showFeed(int uid, int* l)
{
	int *followed_by_me_count = (int*)malloc(sizeof(int));

	int *len2 = (int*)malloc(sizeof(int));
	struct tweetfile** user_tweets = getUserTweets(uid, len2);
	int total_len = *len2;
	struct tweet** all_tweets = (struct tweet**)malloc((total_len)*sizeof(struct tweet*));

	for (int i = 0; i < total_len; i++)
	{
		struct tweet* all_tweet = (struct tweet*)malloc(sizeof(struct tweet));
		all_tweet->tid = user_tweets[i]->tid;
		all_tweet->tweet_text = user_tweets[i]->tweet;
		all_tweet->uid = user_tweets[i]->uid;
		//all_tweet->count_of_retweets_and_likes = user_tweets[i]->count;
		all_tweets[i] = all_tweet;

	}



	struct followersfile** followed_by_me = getUserFollowing(uid, followed_by_me_count);

	for (int j = 0; j < (*followed_by_me_count); j++)
	{
		user_tweets = getUserTweets(followed_by_me[j]->uid, len2);
		total_len = total_len + (*len2);
		all_tweets = (struct tweet**)realloc(all_tweets, total_len*sizeof(struct tweet*));

		for (int i = 0; i < total_len; i++)
		{
			struct tweet* all_tweet = (struct tweet*)malloc(sizeof(struct tweet));
			all_tweet->tid = user_tweets[i]->tid;
			all_tweet->tweet_text = user_tweets[i]->tweet;
			all_tweet->uid = user_tweets[i]->uid;
			//all_tweet->count_of_retweets_and_likes = user_tweets[i]->count;
			all_tweets[i] = all_tweet;

		}
	}
	*l = total_len;
	return all_tweets;
}

struct tweet **gettweets()
{
	struct tweetfile **temp = getTweets();
	struct tweet **res = (struct tweet**)malloc(sizeof(struct tweet*) * 5);
	for (int i = 0; i < 5; i++)
	{
		res[i] = (struct tweet *)malloc(sizeof(struct tweet));
		res[i]->uid = temp[i]->uid;
		res[i]->tid = temp[i]->tid;
		res[i]->tweet_text = temp[i]->tweet;
		res[i]->username = getUserDetails(temp[i]->uid)->uname;
	}
	return res;
}

int changeUserName(int uid, char* username)
{
	return changeUsername(uid, username);
}

void changePassword(int uid, char *password)
{
	changeUserPassword(uid, password);
}




//int followUser(int uid, char *name)
//{
//	return createFollow(uid, getUserId(name));
//}

int editTweet(int tid, int uid, char *tweet)//;// {}
{
	return updateTweet(tid, uid, tweet);
}

int delTweet(int tid, int uid)
{
	//return 0;
	return deleteTweet(tid, uid);
}

//int favourite(int tid, int uid)
//{
//	//return 0;
//	return addfav(tid, uid);
//}


char **myFollowers(int uid, int *len){
	//struct userfile * userprofile = (struct userfile*) malloc(sizeof(struct userfile) * (*len));
	struct followersfile **followers_file = (struct followersfile**) malloc(sizeof(struct followersfile*) * (*len));
	int i;
	char **followers = (char**)malloc(sizeof(char*) * 300);
	struct followersfile** f_file = getUserFollowers(uid, len);
	for (i = 0; i < *len; i++){
		struct userfile* user_details = getUserDetails(f_file[i]->followeruid);//followers_file[i]->followeruid);
		char *follower = (char*)malloc(30 * sizeof(char));
		follower = user_details->uname;
		followers[i] = follower;
	}

	return followers;
}

char **myFollowing(int uid, int *len){
	//struct userfile * userprofile = (struct userfile*) malloc(sizeof(struct userfile) * (*len));
	struct followersfile **followers_file = (struct followersfile**) malloc(sizeof(struct followersfile*) * (*len));
	int i;
	char **followers = (char**)malloc(sizeof(char*) * 300);
	struct followersfile** f_file = getUserFollowing(uid, len);
	for (i = 0; i < *len; i++){
		struct userfile* user_details = getUserDetails(f_file[i]->uid);
		char *follower = (char*)malloc(30 * sizeof(char));
		follower = user_details->uname;
		followers[i] = follower;
	}

	return followers;
}

void load()
{
	loadData();
}



//char **followedByMe(int uid, int *len){}
//
////int comment(int uid, int tid, char* comment){}
//
//struct user* viewProfile(char *name){}



int validate_user(char* username, char *password, char *email)
{
	int check = getUserId(username);
	if (check == -1)
	{
		createUser(username, password, email);
		return 0;
	}
	else
	{
		return 1;
	}
}

void storeUser(char);
int login(char *username, char *password)
{
	//user name checking
	int uid = getUserId(username);
	if (uid != -1)
	{

		struct userfile* user = getUserDetails(uid);
		if (strcmp(password, user->password) == 0)
		{
			return uid;
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}

}
void logout()
{
	updateAll();
}
int postTweet(char *tweet, int uid)
{
	return createTweet(uid, tweet);
}
struct tweet** getMyTweets(int uid, int *lent)
{
	int i;
	struct tweetfile** tweets = getUserTweets(uid, lent);
	struct tweet **mytweets = (struct tweet**)malloc(*lent * sizeof(tweet));
	for (i = 0; i < 30; i++)
	{
		mytweets[i] = (struct tweet*)malloc(sizeof(struct tweet));
	}
	for (i = 0; i < *lent; i++)
	{
		mytweets[i]->tweet_text = tweets[i]->tweet;
		mytweets[i]->tid = tweets[i]->tid;
		mytweets[i]->uid = tweets[i]->tid;
		struct userfile *forusername = getUserDetails(uid);
		mytweets[i]->username = forusername->uname;
	}
	return mytweets;

}
struct user* displayUsersProfile(int uid)
{
	struct user* myprofile=(struct user*)malloc(sizeof(struct user)*1);
	struct userfile* userdata = getUserDetails(uid);
	myprofile->uid = uid;
	myprofile->username=userdata->uname;
	myprofile->email=userdata->email;
	/*struct followersfile **followers = (struct followersfile**)malloc(300 * sizeof(followersfile*));
	int i;
	for (i = 0; i < 300; i++)
	{
		followers[i] = (struct followersfile*)malloc(sizeof(struct followersfile));
	}*/
	int len_followers=0;

	getUserFollowers(uid, &len_followers);
	int len_following = getFollowing(uid);

	myprofile->followers = len_followers;
	myprofile->following = len_following;
	int my_tweet_count;
	getMyTweets(uid, &my_tweet_count);
	myprofile->my_tweet_count = my_tweet_count;
	return myprofile;

}

int comment(int uid, int tid, char* comment)
{
	int cid = createComment(tid, uid, comment);
	return cid;
}

struct user* viewmyprofile(char *username)
{
	int uid = getUserId(username);
	struct user* profile = displayUsersProfile(uid);
	return profile;
}
int likeTweet(int tid, int uid)
{
	int i = addfav(tid, uid);
	return i;
}
int deletetweet(int tid, int uid)
{
	deleteTweet(tid, uid);
	return 1;
}
int favourite(int tid, int uid)
{
	int len=0;
	int i, hasfavorite = 0;
	struct tweetfile** tweets = getUserTweets(uid, &len);
	struct tweet **mytweets = (struct tweet**)malloc(len * sizeof(tweet));
	for (i = 0; i < 30; i++)
	{
		mytweets[i] = (tweet*)malloc(sizeof(tweet));
	}
	for (i = 0; i < len; i++)
	{
		if (tid == tweets[i]->tid && uid == tweets[i]->uid)
		{
			hasfavorite = 1;
			return tweets[i]->count;
		}
	}
	if (hasfavorite == 0)
		return 0;
}
int followUser(int uid, char *name)
{
	int followerid = getUserId(name);
	int following = createFollow(uid, followerid);
	return following;
}



struct tweet** trendingTweets()
{
	int len = 5;
	struct tweetfile** db_tweet = getTweets();
	struct tweet** trending_tweets = (struct tweet**)malloc(len*sizeof(struct tweet*));
	for (int i = 0; i < len; i++){
		struct tweet* new_tweet = (struct tweet*)malloc(sizeof(struct tweet));
		new_tweet->tid = db_tweet[i]->tid;
		new_tweet->tweet_text = db_tweet[i]->tweet;
		new_tweet->uid = db_tweet[i]->uid;
		//	new_tweet->count_of_retweets_and_likes = db_tweet[i]->count;
		trending_tweets[i] = new_tweet;
	}
	return trending_tweets;
}


