//
//  BINDatabaseHandler.h
//  UserManage
//
//  Created by bin on 15/6/24.
//  Copyright (c) 2015年 bin. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <sqlite3.h>

@interface BINDatabaseHandler : NSObject{
    sqlite3 *db;
    NSString * user;
    NSString * image;
}
+ (BINDatabaseHandler *)databaseHandler;
- (BOOL)signinVerify:(NSString*)username withPassword:(NSString*)password;
- (BOOL)signupVerify:(NSString*)username;

- (BOOL)signup:(NSString*)username withPassword:(NSString*)password withName:(NSString*)name;
- (NSMutableArray *)getUserList;
- (BOOL)deleteUser:(NSString *)id;
- (BOOL)modifyName:(NSString*)name forUsername:(NSString*)username;
@end
