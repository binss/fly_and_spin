//
//  BINAdminUserListViewControllerTableViewController.m
//  UserManage
//
//  Created by bin on 15/6/24.
//  Copyright (c) 2015年 bin. All rights reserved.
//

#import "BINAdminUserListViewControllerTableViewController.h"
#import "BINDatabaseHandler.h"

@interface BINAdminUserListViewControllerTableViewController ()

@end

@implementation BINAdminUserListViewControllerTableViewController
@synthesize userList;
@synthesize user;

- (void)viewDidLoad {
    [super viewDidLoad];

    // Uncomment the following line to preserve selection between presentations.
    // self.clearsSelectionOnViewWillAppear = NO;
    
    // Uncomment the following line to display an Edit button in the navigation bar for this view controller.
    // self.navigationItem.rightBarButtonItem = self.editButtonItem;
}

- (void)viewWillAppear:(BOOL)animated
{
    userList = [NSMutableArray arrayWithArray:[[BINDatabaseHandler databaseHandler] getUserList]];
    [self.tableView reloadData];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

-(void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    if([segue.identifier isEqualToString:@"userDetail"])
    {
        NSLog(@"send");
        id theSegue = segue.destinationViewController;
        [theSegue setValue:user forKey:@"userDetail"];
    }
}

#pragma mark - Table view data source

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    
    return [userList count];
}

- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSUInteger row = [indexPath row];
    static NSString *CellIdentifier = @"Cell";
    UITableViewCell *cell = [tableView dequeueReusableCellWithIdentifier:CellIdentifier];
    
    if (cell == nil)
    {
        cell = [[UITableViewCell alloc]initWithStyle:UITableViewCellStyleDefault reuseIdentifier:CellIdentifier];
    }
    cell.textLabel.text = [NSString stringWithFormat:@"%@    %@",[[userList objectAtIndex:row] objectForKey:@"username"],[[userList objectAtIndex:row] objectForKey:@"name"]];
    return cell;
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSUInteger row = [indexPath row];
    user = [NSDictionary dictionaryWithDictionary:[userList objectAtIndex:row]];
//    [[BINDatabaseManager databaseManager] getUserDetail:[dayContentArray objectAtIndex:row]];
    [self performSegueWithIdentifier:@"userDetail" sender:self];
    
    
}


- (void)tableView:(UITableView *)tableView commitEditingStyle:(UITableViewCellEditingStyle)editingStyle forRowAtIndexPath:(NSIndexPath *)indexPath
{
    NSUInteger row = [indexPath row];
    [[BINDatabaseHandler databaseHandler] deleteUser:[[userList objectAtIndex:row] objectForKey:@"id"]];
    [userList removeObjectAtIndex:row];
    
    //更新视图
    [tableView deleteRowsAtIndexPaths:[NSArray arrayWithObject:indexPath]
                     withRowAnimation:UITableViewRowAnimationAutomatic];
}


@end
