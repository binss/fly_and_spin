//
//  UserDetailViewController.h
//  UserManage
//
//  Created by bin on 15/6/26.
//  Copyright (c) 2015年 bin. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface UserDetailViewController : UIViewController<UIImagePickerControllerDelegate, UINavigationControllerDelegate>{
    NSString * username;
}
@property(nonatomic, weak) NSDictionary *userDetail;
@property (weak, nonatomic) IBOutlet UILabel *usernameLabel;
@property (weak, nonatomic) IBOutlet UILabel *nameLabel;
@property (weak, nonatomic) IBOutlet UILabel *timeLabel;
@property (weak, nonatomic) IBOutlet UIImageView *userImageView;

@end
