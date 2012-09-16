/******************************************************************************
 *         __  __           _     _         ____  _       _                   *
 *        |  \/  |_   _  __| | __| |_   _  |  _ \| | __ _(_)_ __  ___         *
 *        | |\/| | | | |/ _` |/ _` | | | | | |_) | |/ _` | | '_ \/ __|        *
 *        | |  | | |_| | (_| | (_| | |_| | |  __/| | (_| | | | | \__ \        *
 *        |_|  |_|\__,_|\__,_|\__,_|\__, | |_|   |_|\__,_|_|_| |_|___/        *
 *                                  |___/                                     *
 *                                                                            *
 *    (C) 2010 by Ryan Jennings <c0der78@gmail.com> www.ryan-jennings.net     *
 *	           Many thanks to creators of muds before me.                     *
 *                                                                            *
 *        In order to use any part of this Mud, you must comply with the      *
 *     license in 'license.txt'.  In particular, you may not remove either    *
 *                        of these copyright notices.                         *
 *                                                                            *
 *       Much time and thought has gone into this software and you are        *
 *     benefitting.  I hope that you share your changes too.  What goes       *
 *                            around, comes around.                           *
 ******************************************************************************/

 /*
  * ! @header Structure, methods and constants related to accounts @ignore 
  * __ACCOUNT_H_ 
  */
#ifndef __ACCOUNT_H_
#define __ACCOUNT_H_

/*!
 * @typedef Account 
 */
typedef struct Account Account;
/*!
 * @typedef AccountPlayer 
 */
typedef struct AccountPlayer AccountPlayer;
/*!
 * @typedef AccountForum 
 */
typedef struct AccountForum AccountForum;


#define ACCOUNT_TABLE "account"
#define ACCOUNT_FORUM_TABLE "account_forum"

#include <muddyengine/flag.h>
#include <muddyengine/forum.h>
#include <muddyengine/connection.h>
#include <time.h>

/*!
 * @typedef Account @abstract Represents a user account.  An account may 
 * have multiple game characters. @author Ryan Jennings
 * <c0der78@gmail.com> @field login account id used to login @field email
 * email address for account @field password encrypted password for
 * account @field players a list of players linked to the account @field
 * timezone the timezone of the account user @field autologinId id of the
 * player to autologin with @field flags flags that modify account
 * behaviour @field forum the current forum the account is reading. will
 * never be null. @field inProgress the current note in progress. Can be
 * null. @field forumData data cached from all forums @field conn the
 * network connection descriptor @field playing the current player being
 * played 
 */
struct Account {
	identifier_t id;
	const char *login;
	const char *email;
	const char *password;
	AccountPlayer *players;
	int timezone;
	identifier_t autologinId;
	Flag *flags;
	Forum *forum;
	Note *inProgress;
	Connection *conn;
	Character *playing;
	AccountForum *forumData;
};

/*!
 * @struct AccountPlayer @abstract a player associated with an account
 * @field charId the character id @field name the character name @field
 * level the character level 
 */
struct AccountPlayer {
	AccountPlayer *next;
	identifier_t charId;
	const char *name;
	short level;
};

/*!
 * @struct AccountForum @abstract a forum associated with an account
 * @field lastNote the last note read in the forum @field unsubscribed
 * false if account is subscribed to the forum @field draft any saved
 * drafts of a note in the forum 
 */
struct AccountForum {
	identifier_t forumId;
	identifier_t id;
	time_t lastNote;
	bool unsubscribed;
	const char *draft;
};

/*!
 * @enum Account Flags @abstract flags for controlling account behaviour
 * @constant ACC_COLOR_OFF controls whether the account connection display
 * color text @discussion 
 */
enum {
	ACC_COLOR_OFF
};

/*!
 * @const account_flags @abstract the table used for account flag /
 * string conversion 
 */
extern const Lookup account_flags[];

/*!
 * @group Memory Management 
 */

/*!
 * creates a new account @return a newly allocated account 
 */
Account *new_account(Connection *);
/*!
 * create a account player link and performs initialization @return a
 * newly allocated account player link 
 */
AccountPlayer *new_account_player();
/*!
 * performs cleanup and destroys a created account @param account the
 * allocated account to destroy 
 */
void destroy_account(Account *);
/*!
 * performs cleanup and destroys a created account player link @param
 * accountPlayer the allocated account player link to destroy 
 */
void destroy_account_player(AccountPlayer *);

/*!
 * @group Memory Management 
 */

/*!
 * @group Data Management 
 */

/*!
 * loads the players for an account @param account the allocated account 
 * to load players for 
 */
int load_account_players(Account *);

/*!
 * loads the forum data for an account @param account the allocated
 * account to load forum data for 
 */
int load_account_forums(Account *);

/*!
 * loads the account for the login @param account the allocated account
 * to load into @param login the login id of the account to load @return 1 
 * if successfull otherwise 0 
 */
int load_account(Account *, const char *);
/*!
 * deletes an account record from saved data @param account the account
 * to delete @return 1 if successfull otherwise 0 
 */
int delete_account(Account *);
/*!
 * saves an account to records @param account the account to save
 * @return 1 if successfull otherwise 0 
 */
int save_account(Account *);

/*!
 * @group Data Management 
 */

/*!
 * @param account the account to get value from @return the last read
 * note for the current forum 
 */
time_t account_forum_last_note(Account *);

/*!
 * @param account the account to get value from @return true if account
 * is subscribed to current forum 
 */
bool account_forum_is_subscribed(Account *);

/*!
 * sets the last note timestamp for the current forum @param account the 
 * account to set value for @param time the created time of the last note 
 */
void account_forum_set_last_note(Account *, time_t);

#endif
