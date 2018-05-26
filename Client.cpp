#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include "db.h"
#include "server.h"

#define TWEETSIZE 255
#define STRINGSIZE 255


int view_login_page();
void view_sign_up_page();
void view_users_profile(struct user *);
int view_features();
int view_and_get_searched_result_features();
void execute_features(struct user*, int, int);
void postTweet(int);

void view_users_profile(struct user *u)
{

	printf("\n\tHi : %s\n\n", u->username);
	printf("\n\tEmail Id : %s\n\n\t", u->email);
	printf("%-20s", "My Tweets");
	printf("%-20s", "Followers");
	printf("%-20s", "Following");
	printf("\n\t");
	printf("%-20d", u->my_tweet_count); //tweet count
	printf("%-20d", u->followers); //followers
	printf("%-20d", u->following); //following	
	printf("\n\n");

	return;
}

void view_sign_up_page()                   //viewing signup page
{

	printf("\n\n \t\t\t\t\t ******SIGN UP ****** \n");

	char * username;
	char * pwd;
	username = (char *)malloc(STRINGSIZE * sizeof(char));
	pwd = (char *)malloc(STRINGSIZE * sizeof(char));
	char *mail;
	mail = (char *)malloc(STRINGSIZE * sizeof(char));
	printf("\n\n\t Username : ");
	fflush(stdin);
	scanf(" %[^\n]s", username);
	printf("\n\n\t Password : ");
	fflush(stdin);
	scanf(" %[^\n]s", pwd);
	printf("\n\n\t Email : ");
	fflush(stdin);
	scanf(" %[^\n]s", mail);
	system("cls");

	int flag = validate_user(username, pwd, mail); // return 1 if unique;
	if (flag == 0){
		printf("\n\t Successfully Signed in !!\n");
		//storeUser(username, pwd, mail);
		return;
	}
	else{
		printf("\nUsername already Taken. please try another Username \n");
		view_sign_up_page();
	}

}

int view_login_page()                   //viewing login page
{

	printf("\n\n \t\t\t\t\t ****** LOGIN ****** \n");
	int login_flag;
	int feat_flag;
	char *username;
	char * pwd;
	username = (char *)malloc(STRINGSIZE * sizeof(char));
	pwd = (char *)malloc(STRINGSIZE * sizeof(char));
	printf("\n\n\t Username : ");
	scanf(" %[^\n]", username);
	printf("\n\t Password : ");
	scanf(" %[^\n]", pwd);
	login_flag = login(username, pwd); // return uId

	system("cls");

	if (login_flag == -1){
		printf("\n\n\t Invalid Credentials. Please try again .");
		view_login_page();
	}
	else{
		system("cls");
		return login_flag;
	}
}

int displayMainMenu(){

	int choice;
	printf("\n\t 1. Login");
	printf("\n\t 2. Sign Up");
	printf("\n\t 3. Exit");
	printf("\n\n\t Enter your choice : ");
	scanf("%d", &choice);

	system("cls");

	if (choice != 1 && choice != 2 && choice != 3){
		printf("\n\n \t\t\t\t\t ****** Welcome to Twitter ****** \n");
		printf("\n\n\t Invalid entry. Please select again. !!\n");
		choice = displayMainMenu();
	}

	return choice;
}

int view_features(){
	int feat_flag;
	printf("\n\t1) Post Tweet");
	printf("\n\t2) Show Feed\n");
	printf("\t3) My Tweets\n");
	printf("\t4) Followers\n");
	printf("\t5) Following \n");
	printf("\t6) Trending Tweets\n");
	printf("\t7) Search \n");
	printf("\t8) Settings \n");
	printf("\t9) Logout\n");

	printf("\n\tChoose an option : ");
	scanf("%d", &feat_flag);

	return feat_flag;
}


// MAIN
int main(void)

{
	int choice;
	int uId;
	int flag;
	struct user *currentUser = NULL;
	int option = -1;
	printf("\n\n \t\t\t\t\t ****** Welcome to Twitter ****** \n");

	choice = displayMainMenu();
	loadData();
	switch (choice){
	case 1: uId = view_login_page();
		printf("\n\n\t  Login Successful !!\n\n");
		currentUser = displayUsersProfile(uId);// displays user Informations
		break;
	case 2: view_sign_up_page();
		system("cls");
		uId = view_login_page();
		currentUser = displayUsersProfile(uId);//  displays user Informations
		break;
	case 3: return 0;
	}

	view_users_profile(currentUser);

	while (option != 9){
		//system("cls");
		printf("\n\n \t\t\t\t\t ****** Welcome to Twitter ****** \n");
		option = view_features();
		execute_features(currentUser, uId, option);
	}

	if (option == 9){
		system("cls");
		choice = displayMainMenu();

		switch (choice){
		case 1: uId = view_login_page();
			printf("\n\n\t  Login Successful !!\n\n");
			currentUser = NULL; // getUserInfo(login_flag); displays user Informations
			break;
		case 2: view_sign_up_page();
			uId = view_login_page();
			currentUser = NULL; // getUserInfo(login_flag); displays user Informations
			break;
		case 3: return 0;
		}
	}


	return 0;
}

void post_tweet(int uId){

	system("cls");

	printf("\n\n \t\t\t\t\t ****** Post Tweet ****** \n");

	char* tweet = (char*)malloc(TWEETSIZE * sizeof(char*));
	/*	char **hashtags = (char **)malloc(100 * sizeof(char *));
	int index = 0;
	char c;
	for (int i = 0; i < 100; i++){
	hashtags[i] = (char *)malloc(100 * sizeof(char));
	} */

	printf("\n\t Enter Tweet : \n\t");
	fflush(stdin);
	scanf("%[^\n]s", tweet);

	/*
	while (true){
	printf("\tDo you want to add any hash tags ? (y/n) : ");
	fflush(stdin);
	scanf("%c", &c);
	if (c == 'n')
	break;
	else{
	printf("\n\t Enter Hashtag : ");
	fflush(stdin);

	scanf(" %s", hashtags[index]);
	index++;
	}

	} */

	storetweet(uId,tweet);
}

void myTweets(int uId, int tweetCount){

	struct tweet **temp = getMyTweets(uId,&tweetCount);
	if (temp == NULL)
	{
		printf("No tweets Yet!");
		return;
	}

	int i;
	int j = 0;
	struct comment **com;
	int len = 0;
	for (i = 0; i < tweetCount; i++){
		printf("\t%d\t%s\n", temp[i]->tid, temp[i]->tweet_text);
		len = 0;
		com = NULL; // getComments(temp[i]->tid, &len);
		for (j = 0; j < len; j++){
			printf("\t%s \t %s", com[j]->username, com[j]->comment_text);
		}
	}
}

void getTrending(){
	struct tweet **temp = gettweets();

	int i;
	int j = 0;
	struct comment **com;
	int len = 0;
	for (i = 0; i < 5; i++){
		printf("Tweet:\n");
		printf("\t %s \t %s\n", temp[i]->username, temp[i]->tweet_text);
		len = 0;
		com = getCommentServers(temp[i]->tid, &len);
		printf("Comments:\n");
		for (j = 0; j < len; j++){
			printf("\t%s \t %s\n", com[j]->username, com[j]->comment_text);
		}
		printf("\n");
	}
}

void getFollowers(int uId, int followerCount){

	char ** followers = myFollowers(uId, &followerCount);

	int i;
	for (i = 0; i < followerCount; i++){
		printf("%s\t", followers[i]);
	}
}

void getFollowing(int uId, int followingCount){

	char **following = myFollowing(uId, &followingCount);

	int i;
	for (i = 0; i < followingCount; i++){
		printf("%s\t", following[i]);
	}
}

void searchUser(){

	char* user = (char*)malloc(STRINGSIZE * sizeof(char));

	printf("\n\t Enter Username : ");
	fflush(stdin);
	scanf("%[^\n]", user);
	int len = strlen(user);
	struct userfile *result = getUserDetails(getUserId(user));

	struct user *res = (struct user*)malloc(sizeof(struct user) * 1);
	res->uid = result->uid;
	res->username = result->uname;
	res->email = result->email;
	int count = 0;
	getUserFollowers(res->uid, &count);
	res->followers = count;
	res->following = getFollowing(res->uid);
	res->my_tweet_count = 0;
	view_users_profile(res);
}

void settings(int uId){

	int option;
	char * str = (char*)malloc(STRINGSIZE*sizeof(char));
	int flag = -1;
	printf("\n\n\t 1. Change Username ");
	printf("\n\t 2. Change Password");
	printf("\n\n\t Select Option : ");

	scanf("%d", &option);

	switch (option){
	case 1: printf("\tEnter New Username : ");
		fflush(stdin);
		scanf("%[^\n]s", str);
		if(changeUserName(uId, str) == 0){
		printf("\t Username already exists !! . Please use another username. : ");
		}
		else{
		return;
		}
		break;
	case 2:	printf("\tEnter New Password : ");
		fflush(stdin);
		scanf("%[^\n]s", str);
		changePassword(uId,str);
		break;
	default: 
		printf("\tInvalid !!");

	}

}

void viewFeed(int uId){

	int len = 0;

	struct tweet **feed = NULL; // showFeed(uId, &len); return all tweets

	system("cls");

	int i;
	for (i = 0; i < len; i++){
		printf("\n\t%s\t%s\n", feed[i]->username, feed[i]->tweet_text);
	}
}

void execute_features(struct user* currentUser, int uId, int option){

	switch (option){
	case 1: post_tweet(uId);
		break;
	case 2: viewFeed(uId);
		break;
	case 3: myTweets(uId, currentUser->my_tweet_count);
		break;
	case 4: getFollowers(uId, currentUser->followers);
		break;
	case 5: getFollowing(uId, currentUser->followers);
		break;
	case 6: getTrending();
		break;
	case 7: searchUser();
		break;
	case 8: settings(uId);
		break;
	case 9:updateAll();
		loadData();
		break;
	}

	return;
}

