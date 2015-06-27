//
//  BINDatabaseHandler.m
//  UserManage
//
//  Created by bin on 15/6/24.
//  Copyright (c) 2015年 bin. All rights reserved.
//

#import "BINDatabaseHandler.h"
#import <CommonCrypto/CommonDigest.h>

@implementation BINDatabaseHandler

+ (BINDatabaseHandler *)databaseHandler
{
    static BINDatabaseHandler *databaseHandlerInstance = nil;
    static dispatch_once_t predicate;
    dispatch_once(&predicate, ^{
        databaseHandlerInstance = [[self alloc] init];
        [databaseHandlerInstance connectDatabase];
    });
    return databaseHandlerInstance;
}

- (void)connectDatabase
{
    NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES);
    NSString *documents = [paths objectAtIndex:0];
    NSString *database_path = [documents stringByAppendingPathComponent:@"db.sqlite"];
    NSLog(@"%@",database_path);
    NSFileManager *fileManager = [NSFileManager defaultManager];
    bool existDatabase = YES;
    if ([fileManager fileExistsAtPath:database_path] == NO)
    {
        NSLog(@"数据库未创建");
        existDatabase = NO;
    }
    
    if (sqlite3_open([database_path UTF8String], &db) != SQLITE_OK)
    {
        sqlite3_close(db);
        NSLog(@"数据库打开失败");
    }
    else
    {
        // 如果数据库未创建，则创建表
        if(!existDatabase)
        {
            char *errMsg;
            const char *sql_stmt = "CREATE TABLE IF NOT EXISTS USER(id INTEGER PRIMARY KEY AUTOINCREMENT, username TEXT, password TEXT, name TEXT, time TEXT)";
            if (sqlite3_exec(db, sql_stmt, NULL, NULL, &errMsg)!=SQLITE_OK)
            {
                NSLog(@"创建表失败");
            }
            else
            {
                NSLog(@"创建表成功");
                [self signup:@"admin" withPassword:@"123456" withName:@"admin"];
                NSLog(@"管理员帐号创建成功");
                
            }
        }
        
        // 创建图片文件夹
        NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory,NSUserDomainMask, YES);
        NSString *directoryPath = [[paths objectAtIndex:0] stringByAppendingPathComponent:@"UserImage"];
        // 保存文件路径
        if([[NSFileManager defaultManager] createDirectoryAtPath:directoryPath withIntermediateDirectories:YES attributes:nil error:nil]){
            NSLog(@"创建图片文件夹成功");
        }
        else{
            NSLog(@"创建图片文件夹失败");

        }
        
    }
}


- (NSDictionary *)signin:(NSString*)username withPassword:(NSString*)password{
    
    NSString *sql = [NSString stringWithFormat:@"SELECT id, name, time FROM USER WHERE username ='%@' and password = '%@'", username, [self md5Encrypt:password]];
    
    sqlite3_stmt *statement;
    
    
    if (sqlite3_prepare_v2(db, [sql UTF8String], -1, &statement, nil) == SQLITE_OK)
    {
        if (sqlite3_step(statement) == SQLITE_ROW)
        {
            NSString *id = [[NSString alloc] initWithUTF8String:(char *)sqlite3_column_text(statement, 0)];
            NSString *name = [[NSString alloc] initWithUTF8String:(char *)sqlite3_column_text(statement, 1)];
            NSString *time = [[NSString alloc] initWithUTF8String:(char *)sqlite3_column_text(statement, 2)];
            NSDictionary *user = @{@"id":id, @"username":username, @"name":name, @"password":password, @"time":time};
            sqlite3_finalize(statement);
            return user;
        }
    
        sqlite3_finalize(statement);
        return false;

    }
    return false;
}

- (BOOL)signup:(NSString*)username withPassword:(NSString*)password withName:(NSString*)name{
    NSDateFormatter *formatter =[[NSDateFormatter alloc] init];
    [formatter setDateFormat:@"yyyy-MM-dd HH:mm:ss"];
    NSString *time = [formatter stringFromDate:[NSDate date]];
    NSString *sql = [NSString stringWithFormat:
                     @"INSERT INTO USER (username, password, name, time) VALUES ('%@', '%@', '%@', '%@')", username, [self md5Encrypt:password], name, time];
    char *errorMsg = NULL;
    if (sqlite3_exec(db, [sql UTF8String], NULL, NULL, &errorMsg) != SQLITE_OK) {
//        sqlite3_close(db);
        return false;
    }
    return true;

}

- (BOOL)signupVerify:(NSString*)username{
    NSString *sql = [NSString stringWithFormat:@"SELECT * FROM USER WHERE username = '%@'", username];
    
    sqlite3_stmt *statement;
    
    if (sqlite3_prepare_v2(db, [sql UTF8String], -1, &statement, nil) == SQLITE_OK)
    {

        if (sqlite3_step(statement) == SQLITE_ROW)
        {
            // 用户已存在
            sqlite3_finalize(statement);
            return true;
        }
        
        sqlite3_finalize(statement);
        return false;
        
    }
    return false;
}

- (BOOL)modifyName:(NSString*)name forUsername:(NSString*)username{
    NSString *sql = [NSString stringWithFormat:@"UPDATE USER SET name = '%@' WHERE username = '%@'", name, username];
    
    sqlite3_stmt *statement;
    
    if (sqlite3_prepare_v2(db, [sql UTF8String], -1, &statement, nil) == SQLITE_OK)
    {
        if (sqlite3_step(statement) == SQLITE_DONE)
        {
            // 修改成功
            sqlite3_finalize(statement);
            return true;
        }
        
        sqlite3_finalize(statement);
        return false;
        
    }
    return false;
}

- (NSMutableArray *)getUserList{
    NSString *sql = @"SELECT id,username,password,name,time FROM USER WHERE username != 'admin'";
    
    sqlite3_stmt *statement;
    NSMutableArray *userList = [NSMutableArray array];

    if (sqlite3_prepare_v2(db, [sql UTF8String], -1, &statement, nil) == SQLITE_OK)
    {
        
        while (sqlite3_step(statement) == SQLITE_ROW)
        {
            NSString *id = [[NSString alloc] initWithUTF8String:(char *)sqlite3_column_text(statement, 0)];
            NSString *username = [[NSString alloc] initWithUTF8String:(char *)sqlite3_column_text(statement, 1)];
            NSString *password = [[NSString alloc] initWithUTF8String:(char *)sqlite3_column_text(statement, 2)];
            NSString *name = [[NSString alloc] initWithUTF8String:(char *)sqlite3_column_text(statement, 3)];
            NSString *time = [[NSString alloc] initWithUTF8String:(char *)sqlite3_column_text(statement, 4)];

            [userList addObject:@{@"id":id, @"username":username, @"name":name, @"password":password, @"time":time}];
        }
        
        sqlite3_finalize(statement);
    }
    return userList;
}

- (BOOL)deleteUser:(NSString *)id{
    sqlite3_stmt *statement;
    NSString *sql = [NSString stringWithFormat:@"DELETE FROM USER where id = %@", id];
    if (sqlite3_prepare_v2(db, [sql UTF8String], -1, &statement, NULL) == SQLITE_OK){
        if (sqlite3_step(statement) == SQLITE_DONE){
            sqlite3_close(db);
            return true;
        }
        else{
            NSLog(@"no");
            sqlite3_close(db);
            return false;
        }
    }
    return false;

}


-(NSString *) md5Encrypt:(NSString*)string
{
    const char *original_str = [string UTF8String];
    
    unsigned char result[CC_MD5_DIGEST_LENGTH];
    
    CC_MD5(original_str, strlen(original_str), result);
    
    NSMutableString *hash = [NSMutableString string];
    for (int i = 0; i < 16; i++)
        
        [hash appendFormat:@"%02X", result[i]];
    
    return [hash lowercaseString];
    
}
@end
