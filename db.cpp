struct userfile
{
	int uid;
	char *uname, *password, *email;
};
struct tweetfile
{
	int tid, uid, count;
	char *tweet;
};
struct commentsfile
{
	int cid, tid, uid;
	char *comment;
};
struct followersfile
{
	int uid, followeruid;
};
struct favorites
{
	int tid, uid;
};
struct userfile **users;
int countUsers, countTweets, countComments, countFollowers, countfavs;
char *getName(char *buff)
{
	char *res = NULL;
	int i = 0;
	for (i = 0; buff[i] != ';'&&buff[i] != '\n'&&buff[i] != '\0'; i++)
	{
		res = (char *)realloc(res, i + 1);
		res[i] = buff[i];
	}
	res[i] = '\0';
	return res;

}

int changeToInt(char *num)
{
	int sum = 0;
	for (int i = 0; num[i] != '\0'; i++)
		sum = sum * 10 + (num[i] - '0');
	return sum;
}
int strlen(char *a)
{
	int i = 0;
	for (i = 0; a[i] != '\0'; i++)
	{

	}
	return i;
}
struct tweetfile **tweets;

void getUserInfo()
{
	users = NULL;
	FILE *fp = fopen("users.txt", "r");
	int count = 0;
	char *buf = (char *)malloc(1024);
	while (fgets(buf, 1024, fp) != NULL)
	{

		count++;
		users = (struct userfile **)realloc(users, sizeof(struct userfile *)*count);
		users[count - 1] = (struct userfile *)malloc(sizeof(struct userfile));
		users[count - 1]->uid = changeToInt(getName(buf)); buf += strlen(getName(buf)) + 1;
		users[count - 1]->uname = getName(buf); buf += strlen(getName(buf)) + 1;
		users[count - 1]->password = getName(buf); buf += strlen(getName(buf)) + 1;
		users[count - 1]->email = getName(buf); buf += strlen(getName(buf)) + 1;
		buf = (char *)malloc(1024);
		countUsers++;
	}

}
void gettweetsInfo()
{
	tweets = NULL;
	FILE *fp = fopen("tweets.txt", "r");
	int count = 0;
	char *buf = (char *)malloc(1024);
	while (fgets(buf, 1024, fp) != NULL)
	{
		count++;
		tweets = (struct tweetfile **)realloc(tweets, sizeof(struct tweetfile *)*count);
		tweets[count - 1] = (struct tweetfile *)malloc(sizeof(struct tweetfile));
		tweets[count - 1]->tid = changeToInt(getName(buf)); buf += strlen(getName(buf)) + 1;
		tweets[count - 1]->uid = changeToInt(getName(buf)); buf += strlen(getName(buf)) + 1;
		tweets[count - 1]->count = changeToInt(getName(buf)); buf += strlen(getName(buf)) + 1;
		tweets[count - 1]->tweet = getName(buf); buf += strlen(getName(buf)) + 1;
		buf = (char *)malloc(1024);
		countTweets++;

	}
}
struct commentsfile **comments;
void commentsInfo()
{
	comments = NULL;
	FILE *fp = fopen("comments.txt", "r");
	int count = 0;
	char *buf = (char *)malloc(1024);
	while (fgets(buf, 1024, fp) != NULL)
	{
		count++;
		comments = (struct commentsfile **)realloc(comments, sizeof(struct commentsfile *)*count);
		comments[count - 1] = (struct commentsfile *)malloc(sizeof(struct commentsfile));
		comments[count - 1]->cid = changeToInt(getName(buf)); buf += strlen(getName(buf)) + 1;
		comments[count - 1]->tid = changeToInt(getName(buf)); buf += strlen(getName(buf)) + 1;
		comments[count - 1]->uid = changeToInt(getName(buf)); buf += strlen(getName(buf)) + 1;
		comments[count - 1]->comment = getName(buf); buf += strlen(getName(buf)) + 1;
		buf = (char *)malloc(1024);
		countComments++;

	}
}
struct followersfile **followrs;
void followers()
{
	followrs = NULL;
	FILE *fp = fopen("followers.txt", "r");
	int count = 0;
	char *buf = (char *)malloc(1024);
	while (fgets(buf, 1024, fp) != NULL)
	{
		count++;
		followrs = (struct followersfile **)realloc(followrs, sizeof(struct followersfile *)*count);
		followrs[count - 1] = (struct followersfile *)malloc(sizeof(struct followersfile));
		followrs[count - 1]->uid = changeToInt(getName(buf)); buf += strlen(getName(buf)) + 1;
		followrs[count - 1]->followeruid = changeToInt(getName(buf)); buf += strlen(getName(buf)) + 1;
		buf = (char *)malloc(1024);
		countFollowers++;

	}
	fclose(fp);
}

struct favorites **favs;
void getFavs()
{
	favs = NULL;
	FILE *fp = fopen("favorates.txt", "r");
	int count = 0;
	char *buf = (char *)malloc(1024);
	while (fgets(buf, 1024, fp) != NULL)
	{
		count++;
		favs = (struct favorites **)realloc(favs, sizeof(struct favorites *)*count);
		favs[count - 1] = (struct favorites *)malloc(sizeof(struct favorites));
		favs[count - 1]->tid = changeToInt(getName(buf)); buf += strlen(getName(buf)) + 1;
		favs[count - 1]->uid = changeToInt(getName(buf)); buf += strlen(getName(buf)) + 1;
		buf = (char *)malloc(1024);
		countfavs++;
	}
	fclose(fp);
}




struct userfile *getUserDetails(int uid1)
{
	int i = 0;
	struct userfile *temp;
	for (i = 0; i<countUsers; i++)
		if (users[i]->uid == uid1)
			return users[i];
	return NULL;
}




struct userfile *createUser(char *username, char *pass, char *email)
{
	users = (struct userfile **)realloc(users, sizeof(struct userfile)*(countUsers + 1));
	users[countUsers] = (struct userfile *)malloc(sizeof(struct userfile));
	countUsers++;
	users[countUsers - 1]->email = email; 
	users[countUsers - 1]->password = pass;
	users[countUsers - 1]->uname = username; 
	users[countUsers - 1]->uid = countUsers;
	return users[countUsers - 1];
}
struct tweetfile **getUserTweets(int uid, int *tweetCount)
{
	int i = 0, j = 0;
	struct tweetfile **temp = NULL;
	for (i = 0; i < countTweets; i++)
	{
		if (tweets[i]->uid == uid)
		{
			j++;
			temp = (struct tweetfile **)realloc(temp, (sizeof(struct tweetfile*)*(j + 1)));
			temp[j - 1] = tweets[i];

		}

	}
	*tweetCount = j;
	return temp;
}
struct followersfile **getUserFollowers(int uid, int *numberOfFolowers)
{
	struct followersfile **temp = NULL;
	int i, j = 0;
	for (i = 0; i < countFollowers; i++)
	{
		if (followrs[i]->uid == uid)
		{

			temp = (struct followersfile **)realloc(temp, sizeof(struct followersfile *)*(j + 1));
			temp[j] = followrs[i];
			j++;
		}
	}
	*numberOfFolowers = j;
	return temp;
}

struct followersfile **getUserFollowing(int uid, int *numberOfFolowers)
{
	struct followersfile **temp = NULL;
	int i, j = 0;
	for (i = 0; i < countFollowers; i++)
	{
		if (followrs[i]->followeruid == uid)
		{

			temp = (struct followersfile **)realloc(temp, sizeof(struct followersfile *)*(j + 1));
			temp[j] = followrs[i];
			j++;
		}
	}
	*numberOfFolowers = j;
	return temp;
}


int changeUsername(int uid, char *name)
{
	int index;
	for (int i = 0; i < countUsers; i++)
	{
		if (strcmp(users[i]->uname, name) == 0)
		{
			return 0;
		}
		if (users[i]->uid == uid)
			index = i;
	}
	users[index]->uname = name;
	return 1;
}

int changeUserPassword(int uid, char *pwd)
{
	int index;
	for (int i = 0; i < countUsers; i++)
	{
		if (users[i]->uid == uid)
		{
			users[i]->password = pwd;
			return 1;
		}
	}
	return 0;
}




int createTweet(int uid, char *tweet)
{
	tweets = (struct tweetfile **)realloc(tweets, sizeof(struct tweetfile *)*(countTweets + 1));
	tweets[countTweets] = (struct tweetfile *)malloc(sizeof(struct tweetfile));
	tweets[countTweets]->tid = tweets[countTweets - 1]->tid + 1;
	tweets[countTweets]->count = 0;
	tweets[countTweets]->uid = uid;
	(tweets[countTweets++])->tweet = tweet;
	return 1;
}
int getUserId(char *name)
{
	int i = 0;
	for (i = 0; i < countUsers; i++)
	{
		if (strcmp(users[i]->uname, name) == 0)
			return users[i]->uid;
	}
	return -1;
}

int createComment(int tid, int uid, char *comment)
{
	int last_cid = comments[countComments - 1]->cid;
	comments = (struct commentsfile **)realloc(comments, sizeof(struct commentsfile*)*(countComments + 1));
	comments[countComments] = (struct commentsfile*)malloc(sizeof(struct commentsfile) * 1);
	comments[countComments]->cid = last_cid + 1;
	comments[countComments]->uid = uid;
	comments[countComments]->tid = tid;
	comments[countComments++]->comment = comment;
	return 1;
}



int addfav(int tid, int uid){
	favs = (struct favorites **)realloc(favs, sizeof(struct favorites *)*(countfavs + 1));
	favs[countfavs] = (struct favorites *)malloc(sizeof(struct favorites));
	favs[countfavs]->tid = tid;
	favs[countfavs]->uid = uid;
	for (int i = 0; i < countTweets; i++)
	{
		if (tweets[i]->tid == tid)
			tweets[i]->count++;
	}
	countfavs++;
	return 1;
}





int createFollow(int uid, int fuid){
	followrs = (struct followersfile **)realloc(tweets, sizeof(struct followersfile *)*(countFollowers + 1));
	followrs[countFollowers] = (struct followersfile *)malloc(sizeof(struct followersfile));
	followrs[countFollowers]->uid = uid;
	followrs[countFollowers]->followeruid = fuid;
	countFollowers++;
	return 0;
}


int updateTweet(int tid, int uid, char *tweet){
	for (int i = 0; i < countTweets; i++){
		if (tweets[i]->tid == tid && users[i]->uid == uid){
			free(tweets[i]->tweet);
			tweets[i]->tweet = tweet;
			tweets[i]->count++;
			return 1;
		}
	}
	return 0;
}


struct tweetfile **getTweets()
{
	struct tweetfile **res = (struct tweetfile **)malloc(sizeof(struct tweetfile *) * 5);
	int LastMax = -1, max, counter = 0;
	while (counter< countTweets)
	{
		max = -1;
		for (int j = 0; j < countTweets; j++)
		{
			if (tweets[j]->count > max)
			{
				if (tweets[j]->count< LastMax || LastMax == -1)
				{
					max = tweets[j]->count;
				}
			}
		}
		for (int k = 0; k < countTweets; k++)
		{
			if (tweets[k]->count == max)
			{
				for (int l = 0; l <= countTweets; l++)
				{
					//store
					res[counter] = tweets[k];

				}
				counter++;
			}
		}
		LastMax = max;
	}
	return res;
}




int updateUsers()
{
	FILE *fp = fopen("users.txt", "w");
	for (int i = 0; i < countUsers; i++)
	{
		fprintf(fp, "%d;", users[i]->uid);
		fprintf(fp, "%s;", users[i]->uname);
		fprintf(fp, "%s;", users[i]->password);
		fprintf(fp, "%s\n", users[i]->email);
	}
	fclose(fp);
	return 1;
}


int updateTweets()
{
	FILE *fp = fopen("tweets.txt", "w");
	for (int i = 0; i < countTweets; i++)
	{
		fprintf(fp, "%d;", tweets[i]->tid);
		fprintf(fp, "%d;", tweets[i]->uid);
		fprintf(fp, "%d;", tweets[i]->count);
		fprintf(fp, "%s\n", tweets[i]->tweet);
	}
	fclose(fp);
	return 1;
}

int updateComment()
{
	FILE *fp = fopen("comments.txt", "w");
	for (int i = 0; i < countComments; i++)
	{
		fprintf(fp, "%d;", comments[i]->cid);
		fprintf(fp, "%d;", comments[i]->tid);
		fprintf(fp, "%d;", comments[i]->uid);
		fprintf(fp, "%s\n", comments[i]->comment);
	}
	fclose(fp);
	return 1;
}

int updateFollowers()
{
	FILE *fp = fopen("followers.txt", "w");
	for (int i = 0; i < countFollowers; i++)
	{
		fprintf(fp, "%d;", followrs[i]->uid);
		fprintf(fp, "%d\n", followrs[i]->followeruid);
	}
	fclose(fp);
	return 1;
}

int updateFavorites()
{
	FILE *fp = fopen("favorates.txt", "w");
	for (int i = 0; i < countfavs; i++)
	{
		fprintf(fp, "%d;", favs[i]->tid);
		fprintf(fp, "%d\n", favs[i]->uid);
	}
	fclose(fp);
	return 1;
}

int deleteTweet(int tid, int uid){
	for (int i = 0; i < countTweets; i++){
		if (tweets[i]->tid == tid && users[i]->uid == uid){
			for (int j = i + 1; j < countTweets; j++){
				tweets[j - 1] = tweets[j];
			}
			countTweets--;
			break;
		}
	}
	for (int i = 0; i < countComments; i++){
		if (comments[i]->tid == tid){
			for (int j = i + 1; j < countComments; j++){
				comments[j - 1] = comments[j];
			}
			countComments--;
		}
	}
	return 0;
}
struct commentsfile **getComments(int tid, int *noc)
{
	struct commentsfile **res = NULL;
	int j = 0;
	for (int i = 0; i < countComments; i++)
	{

		if (comments[i]->tid == tid)
		{
			res = (struct commentsfile **)realloc(res, sizeof(struct commentsfile *)*(j + 1));
			res[j++] = comments[i];
		}
	}
	*noc = j;
	return res;
}

int getFollowing(int uid){
	int count = 0;
	for (int i = 0; i < countFollowers; i++){
		if (followrs[i]->followeruid == uid)
			count++;
	}
	return count;
}

void loadData()
{
	getUserInfo();
	gettweetsInfo();
	commentsInfo();
	followers();
	getFavs();
}

void updateAll()
{
	updateUsers();
	updateTweets();
	updateComment();
	updateFollowers();
	updateFavorites();
}