//
//  AdminUserListViewControllerTableViewController.h
//  UserManage
//
//  Created by bin on 15/6/24.
//  Copyright (c) 2015年 bin. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface AdminUserListViewControllerTableViewController : UITableViewController
@property (strong,nonatomic) NSMutableArray *userList;
@property (strong,nonatomic) NSDictionary *user;
@end
