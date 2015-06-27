//
//  UserDetailViewController.h
//  UserManage
//
//  Created by bin on 15/6/26.
//  Copyright (c) 2015年 bin. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UserDetailViewController : UIViewController<UIImagePickerControllerDelegate, UINavigationControllerDelegate, UIAlertViewDelegate>{
    NSString * username;
    NSString * name;


}
@property(nonatomic, weak) NSDictionary *userDetail;
@property (weak, nonatomic) IBOutlet UILabel *usernameLabel;
@property (weak, nonatomic) IBOutlet UILabel *nameLabel;
@property (weak, nonatomic) IBOutlet UILabel *timeLabel;
@property (weak, nonatomic) IBOutlet UIImageView *userImageView;
- (IBAction)modifynameButtonPress:(UIButton *)sender;

- (IBAction)startgameButtonPressed:(UIButton *)sender;

@end
