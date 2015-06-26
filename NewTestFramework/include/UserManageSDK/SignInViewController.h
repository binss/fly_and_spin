//
//  SignInViewController.h
//  UserManage
//
//  Created by bin on 15/6/24.
//  Copyright (c) 2015年 bin. All rights reserved.
//

#import <UIKit/UIKit.h>

@interface SignInViewController : UIViewController
@property (weak, nonatomic) IBOutlet UITextField *usernameTextField;

@property (weak, nonatomic) IBOutlet UITextField *passwordTextField;
@property (weak, nonatomic) IBOutlet UIButton *signButton;
- (IBAction)signButtonPressed:(UIButton *)sender;

- (IBAction)usernameEditingChanged:(UITextField *)sender;
- (IBAction)passwordEditingChanged:(UITextField *)sender;
- (void)haha;
@end
