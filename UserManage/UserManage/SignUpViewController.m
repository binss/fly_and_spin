//
//  SignUpViewController.m
//  UserManage
//
//  Created by bin on 15/6/26.
//  Copyright (c) 2015年 bin. All rights reserved.
//

#import "SignUpViewController.h"
#import "BINDatabaseHandler.h"

@interface SignUpViewController ()

@end

@implementation SignUpViewController

- (void)viewDidLoad {
    [super viewDidLoad];
    // Do any additional setup after loading the view.
    self.signupButton.enabled = NO;
    [self.usernameTextField becomeFirstResponder];
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

/*
#pragma mark - Navigation

// In a storyboard-based application, you will often want to do a little preparation before navigation
- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender {
    // Get the new view controller using [segue destinationViewController].
    // Pass the selected object to the new view controller.
}
*/

- (IBAction)signpButtonPressed:(UIButton *)sender {
    if(self.usernameTextField.text.length && self.passwordTextField.text.length && self.nameTextField.text.length){
            if([[BINDatabaseHandler databaseHandler] signupVerify:self.usernameTextField.text] == true){
                UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"提示"
                                                                message:@"用户名已存在！"
                                                               delegate:nil
                                                      cancelButtonTitle:@"OK"
                                                      otherButtonTitles:nil];
                [alert show];
            }
            else{
                if([[BINDatabaseHandler databaseHandler] signup:self.usernameTextField.text withPassword:self.passwordTextField.text withName:self.nameTextField.text]){
                    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"提示"
                                                                    message:@"注册成功！"
                                                                   delegate:self
                                                          cancelButtonTitle:@"OK"
                                                          otherButtonTitles:nil];
                    [alert show];
                }
                else{
                    UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"提示"
                                                                    message:@"注册失败！请重新尝试。"
                                                                   delegate:nil
                                                          cancelButtonTitle:@"OK"
                                                          otherButtonTitles:nil];
                    [alert show];
                }
            }
    }
    else{
        UIAlertView *alert = [[UIAlertView alloc] initWithTitle:@"提示"
                                                        message:@"请输入用户名和密码！"
                                                       delegate:nil
                                              cancelButtonTitle:@"OK"
                                              otherButtonTitles:nil];
        [alert show];
    }
}

- (IBAction)usernameEditingChanged:(UITextField *)sender
{
    [self checkSignupButtonEnabled];
}

- (IBAction)nameEditingChanged:(UITextField *)sender
{
    [self checkSignupButtonEnabled];
    
}

- (IBAction)passwordEditingChanged:(UITextField *)sender
{
    [self checkSignupButtonEnabled];
    
}


- (void)checkSignupButtonEnabled
{
    if(self.usernameTextField.text.length && self.passwordTextField.text.length && self.nameTextField.text.length)
    {
        self.signupButton.enabled = YES;
    }
    else
    {
        self.signupButton.enabled = NO;
    }
    
}

-(void)alertView:(UIAlertView*)alertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    [self.navigationController popViewControllerAnimated:YES];
}

@end
